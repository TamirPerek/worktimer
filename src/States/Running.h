#pragma once

#include "State_Interface.h"
#include <chrono>
#include <string>

namespace State
{
    class Running : public State_Interface
    {
        std::chrono::system_clock::time_point mStart{std::chrono::system_clock::now()};
        std::string mAddInfos{};
        int databaseID{0};

    public:
        Running();
        explicit Running(const std::string_view &);
        ~Running() noexcept final = default;
        bool Apply(StateMachine &, Command &&) noexcept final;
        void StartTimer() noexcept;
        std::string Name() const noexcept final { return "Running"; }
        std::string GetCommand() const noexcept final { return mAddInfos; }
        Running &setDatabaseID(const int &) noexcept;
    };
}
