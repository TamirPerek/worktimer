//
//  Exception.hpp
//  WorkTimer
//
//  Created by Nils Brödner on 01.10.21.
//

#pragma once

#include "spdlog/fmt/fmt.h"

namespace Exception
{
    void handle() noexcept;

    class DatabaseException : public std::runtime_error
    {
    public:
        explicit DatabaseException(const std::string &xIn) : std::runtime_error{xIn} {};
    };

    class StateException : public std::runtime_error
    {
    public:
        explicit StateException(const std::string &xIn) : std::runtime_error{xIn} {};
    };

    class DumpException : public std::runtime_error
    {
    public:
        explicit DumpException(const std::string &xIn) : std::runtime_error{xIn} {};
    };
}

#define THROWDB(n, a...) throw Exception::DatabaseException(fmt::format(n, a));
#define THROWSTATE(n, a...) throw Exception::StateException(fmt::format(n, a));
#define THROWDUMP(n, a...) throw Exception::DumpException(fmt::format(n, a));