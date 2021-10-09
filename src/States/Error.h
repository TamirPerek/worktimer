#pragma once

#include "State_Interface.h"

namespace State
{
    class Error : public State_Interface
    {
    public:
        ~Error() noexcept final = default;
        bool Apply(StateMachine &, Command &&) noexcept final;
        std::string Name() const noexcept final { return "Error"; }
        std::string GetCommand() const noexcept final { return ""; }
    };
}