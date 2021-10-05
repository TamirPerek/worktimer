#pragma once

struct LogData;

class Database
{
public:
    static bool write(const LogData &) noexcept;
};
