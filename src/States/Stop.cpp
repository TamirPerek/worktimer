#include "Stop.h"

#include "Start.h"

#include "../Command.h"
#include "../Logger.h"
#include "../StateMachine.h"

#include <iostream>
#include <filesystem>

namespace State
{
    Stop::Stop(StateMachine &xStateMachine, const std::string_view &xMsg) noexcept
    {
        Logger::getInstance().getLogger()->info("{}", xMsg);
        Logger::getInstance().getLogger()->flush();

        std::shared_ptr<Start> tNewState = std::make_shared<Start>();
        xStateMachine.SetSate(tNewState);
    }
    bool Stop::Apply(StateMachine &, const Command &) noexcept
    {
        return false;
    }
} // namespace State
