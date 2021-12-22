#include "Database_Category.h"

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

constexpr static std::string_view gTableName{"categories"};

static vdk::signal<void()> gDatabaseEvent;

bool Database_Category::execute(const std::string_view &xSQLCommand, int64_t &xLastInsertedRowIDint, int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
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

bool Database_Category::update(const Database_Category_DTO &xDTO) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("UPDATE {} SET text = '{}' WHERE id = {};",
                                               gTableName,
                                               xDTO.text,
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

int Database_Category::insert(const Database_Category_DTO &xDTO) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("INSERT INTO {} (text) VALUES('{}');",
                                               gTableName,
                                               xDTO.text);

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

bool Database_Category::read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
{
    try
    {
        auto tSQLStatement = fmt::format("SELECT * FROM {}", gTableName);

        int64_t tRowID;
        return execute(tSQLStatement, tRowID, xCallback, xAddInfo);
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}

bool Database_Category::remove(const Database_Category_DTO &xDTO) noexcept
{
    try
    {
        auto tSQLStatement = fmt::format("DELETE FROM {} WHERE id = {};",
                                         gTableName,
                                         xDTO.id);
        int64_t tRowID;
        if (!execute(tSQLStatement, tRowID))
            THROWDB("Unable to delete data in database, ID: <{}>", xDTO.id);

        getDatabaseEvent().emit();

        return true;
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}

vdk::signal<void()> &Database_Category::getDatabaseEvent() noexcept
{
    return gDatabaseEvent;
}
