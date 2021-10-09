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

bool Database::execute(const std::string_view &xSQLCommand, int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
{
    sqlite3 *tDB = nullptr;
    
    try
    {
        const auto gTestDBPath = std::filesystem::current_path() / StaticData::pathToDB;

        if (std::error_code er; !std::filesystem::exists(gTestDBPath, er))
            THROWDB("file does not exist: {}, {}", gTestDBPath.string(), er.message());

        if (const auto rc = sqlite3_open(gTestDBPath.string().c_str(), &tDB); rc != SQLITE_OK)
            THROWDB("Can not open Database: {}", rc);

        if (const auto rc = sqlite3_exec(tDB, xSQLCommand.data(), xCallback, xAddInfo, nullptr); rc != SQLITE_OK)
            THROWDB("Can't execute Database querry: {}", rc);

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

bool Database::write(const LogData &xDTO) noexcept
{
    try
    {
        const auto tSQLStatement = fmt::format("INSERT INTO worklog (desc, start, end, duration) VALUES('{}', {}, {}, {});",
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration);

        return execute(tSQLStatement);
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}

bool Database::read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo) noexcept
{
    try
    {
        constexpr static std::string_view tSQLStatement{"SELECT * FROM worklog"};

        return execute(tSQLStatement, xCallback, xAddInfo);
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}