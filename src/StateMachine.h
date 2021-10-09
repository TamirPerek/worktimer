#pragma once

#include "States/State_Interface.h"
#include "States/Start.h"

#include <memory>

class Command;

class StateMachine
{
private:
    std::unique_ptr<State::State_Interface> mState{std::make_unique<State::Start>()};

public:
    StateMachine() = default;
    explicit StateMachine(std::unique_ptr<State::State_Interface> &&) noexcept;
    ~StateMachine() noexcept;

    StateMachine &SetSate(std::unique_ptr<State::State_Interface> &&) noexcept;
    const std::unique_ptr<State::State_Interface> &GetState() const noexcept;

    std::string GetStatus() const noexcept;

    bool Apply(Command &&) noexcept;
};
