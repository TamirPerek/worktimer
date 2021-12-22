#pragma once

#include <string>
#include <signals.h>
#include <time.h>

struct Database_Category_DTO
{
    int id{0};
    std::string text{};
};

class Database_Category
{
    static bool execute(const std::string_view &xSQLCommand, int64_t &xLastInsertedRowID, int (*xCallback)(void *, int, char **, char **) = nullptr, void *xAddInfo = nullptr) noexcept;

public:
    static bool update(const Database_Category_DTO &) noexcept;
    static int insert(const Database_Category_DTO &) noexcept;
    static bool read(int (*xCallback)(void *, int, char **, char **), void *xAddInfo = nullptr) noexcept;
    static bool remove(const Database_Category_DTO &) noexcept;
    static vdk::signal<void()> &getDatabaseEvent() noexcept;
};
