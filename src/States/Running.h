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

    public:
         Running();
        explicit Running(const std::string_view &);
        ~Running() noexcept override = default;
        bool Apply(StateMachine &, const Command &) noexcept override;
        void StartTimer() noexcept;
        std::string Name() const noexcept override { return "Running"; }
    };
}
