#include "StateMachine.h"

#include "Command.h"
#include "Logger.h"

#include <iostream>

StateMachine::StateMachine(const std::shared_ptr<State::State_Interface> &xIn) noexcept
    : mState{xIn}
{
}

StateMachine::~StateMachine() noexcept
{
    Apply(Command{CommandType::Stop, ""});
}

StateMachine &StateMachine::SetSate(const std::shared_ptr<State::State_Interface> &xIn) noexcept
{
    mState = xIn;
    return *this;
}
const std::shared_ptr<State::State_Interface> &StateMachine::GetState() const noexcept
{
    return mState;
}

bool StateMachine::Apply(const Command &xIn) noexcept
{
    if (xIn.GetType() == CommandType::Error)
    {
        Logger::getInstance().getLogger()->info("Can't Validate Command: {}", xIn.GetAddInfos());
        Logger::getInstance().getLogger()->flush();

        return true;
    }
    else
    {
        return mState->Apply(*this, xIn);
    }
}