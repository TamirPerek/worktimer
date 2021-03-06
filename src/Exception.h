//
//  Exception.hpp
//  WorkTimer
//
//  Created by Nils Brödner on 01.10.21.
//

#pragma once

#include "spdlog/fmt/fmt.h"

#include <signals.h>

#include <string>

namespace Exception
{
    void handle() noexcept;

    vdk::signal<void(std::string)> &getExceptionSignal();

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

    class UIException : public std::runtime_error
    {
    public:
        explicit UIException(const std::string &xIn) : std::runtime_error{xIn} {};
    };
}

constexpr static std::string_view gExceptionText{"{}:{} -> {}"};

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define THROWDB(n, ...) throw Exception::DatabaseException(fmt::format(gExceptionText, __FILENAME__, __LINE__, fmt::format(n, __VA_ARGS__)));
#define THROWSTATE(n, ...) throw Exception::StateException(fmt::format(gExceptionText, __FILENAME__, __LINE__, fmt::format(n, __VA_ARGS__)));
#define THROWDUMP(n, ...) throw Exception::DumpException(fmt::format(gExceptionText, __FILENAME__, __LINE__, fmt::format(n, __VA_ARGS__)));
#define THROWUIERROR(n, ...) throw Exception::UIException(fmt::format(gExceptionText, __FILENAME__, __LINE__, fmt::format(n, __VA_ARGS__)));
