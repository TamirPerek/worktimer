#pragma once

#include <string>

enum class CommandType
{
    Start,
    Stop,
    Error
};

class Command
{
private:
    const CommandType mType{CommandType::Start};
    const std::string mAddInfos{""};
public:
    Command() = delete;
    explicit Command(const CommandType &, const std::string_view &);
    ~Command() = default;

    const CommandType &GetType() const noexcept;
    const std::string &GetAddInfos() const noexcept;
};

