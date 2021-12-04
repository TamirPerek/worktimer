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

constexpr static std::string_view gTableName{"worklog"};

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
        const auto tSQLStatement = fmt::format("UPDATE {} SET desc = '{}', start = {}, end = {}, duration = {} WHERE id = {};",
                                               gTableName,
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration,
                                               xDTO.id);

        int64_t tRowID;
        return execute(tSQLStatement, tRowID);
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
        const auto tSQLStatement = fmt::format("INSERT INTO {} (desc, start, end, duration) VALUES('{}', {}, {}, {});",
                                               gTableName,
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration);

        int64_t tID = 0;
        if (!execute(tSQLStatement, tID))
            THROWDB("Unable to insert data into database", 0);

        return static_cast<int>(tID);
    }
    catch (...)
    {
        Exception::handle();
        return -1;
    }
}

bool Database::read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("SELECT * FROM {}", gTableName);
        int64_t tRowID;
        return execute(tSQLStatement, tRowID, xCallback, xAddInfo);
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}