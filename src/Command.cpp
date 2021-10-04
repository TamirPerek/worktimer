#include "Command.h"

Command::Command(const CommandType &xType, const std::string_view &xAddInfos)
    : mType{xType}, mAddInfos{xAddInfos}
{
}

const CommandType &Command::GetType() const noexcept
{
    return mType;
}
const std::string &Command::GetAddInfos() const noexcept
{
    return mAddInfos;
}