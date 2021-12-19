#pragma once

#include <string>
#include <signals.h>
#include <time.h>

struct LogData;

class Database
{
    static bool execute(const std::string_view &xSQLCommand, int64_t &xLastInsertedRowID, int (*xCallback)(void *, int, char **, char **) = nullptr, void *xAddInfo = nullptr) noexcept;

public:
    static bool update(const LogData &) noexcept;
    static int insert(const LogData &) noexcept;
    static bool read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo = nullptr, const time_t &xFrom = 0, const time_t &xTo = 0) noexcept;
    static vdk::signal<void()> &getDatabaseEvent() noexcept;
};
