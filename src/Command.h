#pragma once

#include <string>

enum class CommandType
{
    Start,
    Stop,
    Error,
    Status,
    Dump
};

class Command
{
private:
    CommandType mType{CommandType::Start};
    std::string mAddInfos{""};
    int mCategory{0};
public:
    Command() = default;
    explicit Command(const CommandType &, const std::string_view &xAddInfos = "", const int &xCategory = 0);
    
    const CommandType &GetType() const noexcept;
    const std::string &GetAddInfos() const noexcept;
    const int &GetCategory() const noexcept;
};

