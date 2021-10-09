#pragma once

#include "State_Interface.h"

namespace State
{
    class Start : public State_Interface
    {
    public:
        ~Start() noexcept final = default;
        bool Apply(StateMachine &, Command &&) noexcept final;
        std::string Name() const noexcept final { return "Start"; }
        std::string GetCommand() const noexcept final { return ""; }
    };
}
