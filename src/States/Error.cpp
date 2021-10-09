#include "Error.h"

#include "../Command.h"
#include "../Logger.h"

#include <iostream>

namespace State
{
    bool Error::Apply(StateMachine &xStateMachine, Command &&xIn) noexcept
    {
        Logger::getInstance().getLogger()->error("Can't Validate Command: {}", xIn.GetAddInfos());
        Logger::getInstance().getLogger()->flush();
        return true;
    }
} // namespace State
