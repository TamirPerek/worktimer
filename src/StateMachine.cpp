#include "StateMachine.h"

#include "Command.h"
#include "Logger.h"
#include "Dump.h"

#include <iostream>

StateMachine::StateMachine(std::unique_ptr<State::State_Interface> &&xIn) noexcept
    : mState{std::move(xIn)}
{
}

StateMachine::~StateMachine() noexcept
{
    Apply(Command{CommandType::Stop});
}

StateMachine &StateMachine::SetSate(std::unique_ptr<State::State_Interface> &&xIn) noexcept
{
    mState = std::move(xIn);
    fmt::print("Acctual state: {}\n", mState->Name());
    return *this;
}
const std::unique_ptr<State::State_Interface> &StateMachine::GetState() const noexcept
{
    return mState;
}

std::string StateMachine::GetStatus() const noexcept
{
    if (mState)
        return mState->Name();
    else
        return "No State set.";
}

bool StateMachine::Apply(Command &&xIn) noexcept
{
    switch (xIn.GetType())
    {
    case CommandType::Error:
    {
        Logger::getInstance().getLogger()->info("Can't Validate Command: {}", xIn.GetAddInfos());
        Logger::getInstance().getLogger()->flush();

        return true;
    }
    case CommandType::Status:
    {
        fmt::print("Acctual state: {}, acctual command: {}\n", mState->Name(), mState->GetCommand());
        return true;
    }
    case CommandType::Dump:
    {
        Dump::DumpDatabase(std::filesystem::current_path() / gDumpPath);
        return true;
    }

    default:
        return mState->Apply(*this, std::move(xIn));
    }
}