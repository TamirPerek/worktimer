#include "Command.h"

Command::Command(const CommandType &xType, const std::string_view &xAddInfos, const int &xCategory)
    : mType{xType}, mAddInfos{xAddInfos}, mCategory{xCategory}
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
const int &Command::GetCategory() const noexcept
{
    return mCategory;
}