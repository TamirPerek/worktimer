#pragma once

#include "../Command.h"
#include <string>

class StateMachine;

namespace State
{
    class State_Interface
    {
    public:
        virtual ~State_Interface() noexcept = default;
        virtual bool Apply(StateMachine &, const Command &) noexcept = 0;
        virtual std::string Name() const noexcept = 0;
    };
}
