#pragma once

#include "State_Interface.h"

namespace State
{
    class Start : public State_Interface
    {
    public:
        ~Start() noexcept override = default;
        bool Apply(StateMachine &, const Command &) noexcept override;
        std::string Name() const noexcept override { return "Start"; }
    };
}
