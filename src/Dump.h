#pragma once

#include <filesystem>
#include <string>

static constexpr std::string_view gDumpPath{"dump.csv"};

class Dump
{
    static int DumpCallback(void *xPath, int xCount, char **cData, char **xColumns);
    static std::string TimeToString(const time_t&) noexcept;

public:
    static void DumpDatabase(const std::filesystem::path &) noexcept;
};