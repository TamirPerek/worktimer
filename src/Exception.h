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

constexpr static std::string_view gExceptionText{"{}:{} -> {}"};

#define THROWDB(n, ...) throw Exception::DatabaseException(fmt::format(gExceptionText, __FILE__, __LINE__, fmt::format(n, __VA_ARGS__)));
#define THROWSTATE(n, ...) throw Exception::StateException(fmt::format(gExceptionText, __FILE__, __LINE__, fmt::format(n, __VA_ARGS__)));
#define THROWDUMP(n, ...) throw Exception::DumpException(fmt::format(gExceptionText, __FILE__, __LINE__, fmt::format(n, __VA_ARGS__)));
