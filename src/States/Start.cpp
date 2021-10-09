#include "Start.h"

#include "Running.h"

#include "../Command.h"
#include "../Exception.h"
#include "../StateMachine.h"

#include <iostream>

namespace State
{
    bool Start::Apply(StateMachine &xStateMachine, Command &&xIn) noexcept
    {
        try
        {
            if (xIn.GetType() != CommandType::Start)
                THROWSTATE("Wrong CommandType, expected {} command", "Start");

            xStateMachine.SetSate(std::make_unique<Running>(xIn.GetAddInfos()));

            return true;
        }
        catch (...)
        {
            Exception::handle();
            return false;
        }
    }
} // namespace State
