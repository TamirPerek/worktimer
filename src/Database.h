#pragma once

#include <string>

struct LogData;

class Database
{
    static bool execute(const std::string_view &xSQLCommand, int (*xCallback)(void *, int, char **, char **) = nullptr, void *xAddInfo = nullptr) noexcept;

public:
    static bool write(const LogData &) noexcept;
    static bool read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo = nullptr) noexcept;
};
