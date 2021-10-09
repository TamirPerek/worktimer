#pragma once

#include <string>

enum class CommandType
{
    Start,
    Stop,
    Error,
    Status
};

class Command
{
private:
    CommandType mType{CommandType::Start};
    std::string mAddInfos{""};
public:
    Command() = default;
    explicit Command(const CommandType &, const std::string_view &xAddInfos = "");
    
    const CommandType &GetType() const noexcept;
    const std::string &GetAddInfos() const noexcept;
};

