#pragma once

#include "States/State_Interface.h"
#include "States/Start.h"

#include <memory>

class Command;

class StateMachine
{
private:
    std::shared_ptr<State::State_Interface> mState{std::make_shared<State::Start>()};

public:
    StateMachine() = default;
    explicit StateMachine(const std::shared_ptr<State::State_Interface> &) noexcept;
    ~StateMachine() noexcept;

    StateMachine &SetSate(const std::shared_ptr<State::State_Interface> &) noexcept;
    const std::shared_ptr<State::State_Interface> &GetState() const noexcept;

    bool Apply(const Command &) noexcept;
};
