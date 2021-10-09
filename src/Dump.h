#pragma once

#include <filesystem>

static constexpr std::string_view gDumpPath{"dump.csv"};

class Dump
{
    static int DumpCallback(void *xPath, int xCount, char **cData, char **xColumns);

public:
    static void DumpDatabase(const std::filesystem::path &) noexcept;
};