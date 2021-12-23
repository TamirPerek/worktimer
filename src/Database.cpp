#include "Database.h"

#include "LogDataDTO.h"
#include "StaticData.h"
#include "Exception.h"

extern "C"
{
#include "../lib/SQLite/sqlite3.h"
}
#include <filesystem>
#include "spdlog/fmt/fmt.h"

#include <iostream>

constexpr static std::string_view gTableName{"worklog"};

static vdk::signal<void()> gDatabaseEvent;

bool Database::execute(const std::string_view &xSQLCommand, int64_t &xLastInsertedRowIDint, int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
{
    sqlite3 *tDB = nullptr;

    try
    {
        const auto gTestDBPath = StaticData::pathToResource / StaticData::pathToDB;

        if (std::error_code er; !std::filesystem::exists(gTestDBPath, er))
            THROWDB("file does not exist: {}, {}", gTestDBPath.string(), er.message());

        if (const auto rc = sqlite3_open(gTestDBPath.string().c_str(), &tDB); rc != SQLITE_OK)
            THROWDB("Can not open Database: {}", rc);

        if (const auto rc = sqlite3_exec(tDB, xSQLCommand.data(), xCallback, xAddInfo, nullptr); rc != SQLITE_OK)
            THROWDB("Can't execute Database querry: {}; {}", rc, xSQLCommand);

        xLastInsertedRowIDint = sqlite3_last_insert_rowid(tDB);

        if (const auto rc = sqlite3_close(tDB); rc != SQLITE_OK)
            THROWDB("Can't close database: {}", rc);

        return true;
    }
    catch (...)
    {
        Exception::handle();
        if (tDB)
            sqlite3_close(tDB);
        return false;
    }
};

bool Database::update(const LogData &xDTO) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("UPDATE {} SET desc = '{}', start = {}, end = {}, duration = {}, category = {} WHERE id = {};",
                                               gTableName,
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration,
                                               xDTO.category,
                                               xDTO.id);

        int64_t tRowID;
        if (!execute(tSQLStatement, tRowID))
            THROWDB("Unable to update data into database", 0);

        getDatabaseEvent().emit();

        return true;
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}

int Database::insert(const LogData &xDTO) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("INSERT INTO {} (desc, start, end, duration, category) VALUES('{}', {}, {}, {}, {});",
                                               gTableName,
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration,
                                               xDTO.category);

        int64_t tID = 0;
        if (!execute(tSQLStatement, tID))
            THROWDB("Unable to insert data into database", 0);

        getDatabaseEvent().emit();

        return static_cast<int>(tID);
    }
    catch (...)
    {
        Exception::handle();
        return -1;
    }
}

bool Database::read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo, const time_t &xFrom, const time_t &xTo) noexcept
{
    try
    {
        auto tSQLStatement = fmt::format("SELECT {}.id, categories.text, desc, start, end, duration, categories.id AS category_id FROM {} JOIN categories ON {}.category = categories.id", gTableName, gTableName, gTableName);

        if (xFrom > 0 && xTo > 0)
        {
            tSQLStatement = fmt::format("{} WHERE start >= {} AND end <= {} ORDER BY {}.id DESC", tSQLStatement, xFrom, xTo, gTableName);
        }

        int64_t tRowID;
        return execute(tSQLStatement, tRowID, xCallback, xAddInfo);
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}

vdk::signal<void()> &Database::getDatabaseEvent() noexcept
{
    return gDatabaseEvent;
}
