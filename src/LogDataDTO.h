#pragma once

#include <string>
#include <chrono>

struct LogData
{
    int id;
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::string description;
    int duration;
    int category;
};