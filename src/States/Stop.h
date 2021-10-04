#pragma once

#include "State_Interface.h"

#include <string>

namespace State
{
    class Stop : public State_Interface
    {
    public:
        Stop() = delete;
        explicit Stop(StateMachine &, const std::string_view &xMsg) noexcept;
        ~Stop() noexcept override = default;
        bool Apply(StateMachine &, const Command &) noexcept override;
        std::string Name() const noexcept override {return "Stop";}
    };
}