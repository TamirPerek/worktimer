#include "StateMachine.h"

// #include "States/Error.h"
#include "Command.h"

// #include "spdlog/fmt/fmt.h"

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
    // fmt::print("New Sate: {}\n", xIn->Name());
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
        std::cerr << "Can't Validate Command:\n"
                  << xIn.GetAddInfos() << std::endl;
        // State::Error tError;
        // return tError.Apply(*this, xIn);
        return true;
    }
    else
    {
        return mState->Apply(*this, xIn);
    }
}