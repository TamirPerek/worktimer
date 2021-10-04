#pragma once

#include "State_Interface.h"

namespace State
{
    class Error : public State_Interface
    {
    public:
        ~Error() noexcept override = default;
        bool Apply(StateMachine &, const Command &) noexcept override;
        std::string Name() const noexcept override { return "Error"; }
    };
}