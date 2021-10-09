#include "Start.h"

#include "Running.h"

#include "../Command.h"
#include "../Exception.h"
#include "../StateMachine.h"

#include <iostream>

namespace State
{
    bool Start::Apply(StateMachine &xStateMachine, const Command &xIn) noexcept
    {
        try
        {
            if (xIn.GetType() != CommandType::Start)
                THROWSTATE("Wrong CommandType, expected {} command", "Start");

            std::shared_ptr<Running> tNewState = std::make_shared<Running>(xIn.GetAddInfos());
            xStateMachine.SetSate(tNewState);

            return true;
        }
        catch (...)
        {
            Exception::handle();
            return false;
        }
    }
} // namespace State
