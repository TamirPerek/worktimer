#pragma once

#include "Command.h"

class CommandParser
{
private:
    /* data */
public:
    CommandParser(/* args */) noexcept = default;
    ~CommandParser() noexcept = default;

    Command read() const noexcept;
};
