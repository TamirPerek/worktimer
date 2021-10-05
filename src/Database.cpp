#include "Database.h"

#include "LogDataDTO.h"
#include "StaticData.h"
#include "Exception.h"

extern "C"
{
#include <sqlite3.h>
}
#include <filesystem>
#include "spdlog/fmt/fmt.h"

bool Database::write(const LogData &xDTO) noexcept
{
    sqlite3 *tDB = nullptr;
    try
    {
        const auto tSQLStatement = fmt::format("INSERT INTO worklog (desc, start, end, duration) VALUES('{}', {}, {}, {});",
                                               xDTO.description,
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.start.time_since_epoch()).count()),
                                               static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(xDTO.end.time_since_epoch()).count()),
                                               xDTO.duration);

        const std::filesystem::path gTestDBPath = StaticData::pathToDB;

        if (!std::filesystem::exists(gTestDBPath.relative_path()))
            throw std::runtime_error(fmt::format("file does not exist: {}", gTestDBPath.string()));

        if (const int rc = sqlite3_open(gTestDBPath.relative_path().string().c_str(), &tDB); rc != SQLITE_OK)
            throw std::runtime_error(fmt::format("Can not open Database: {}", rc));

        if (const int rc = sqlite3_exec(tDB, tSQLStatement.data(), nullptr, nullptr, nullptr); rc != SQLITE_OK)
            throw std::runtime_error(fmt::format("Can't execute Database querry: {}", rc));

        return true;
    }
    catch (...)
    {
        Exception::handle();
        if (tDB)
            sqlite3_close(tDB);
        return false;
    }
}