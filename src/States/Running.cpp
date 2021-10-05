#include "Running.h"

#include "../Command.h"
#include "../Exception.h"
#include "../StateMachine.h"
#include "../Database.h"
#include "../LogDataDTO.h"

#include "spdlog/fmt/fmt.h"

#include <iostream>

namespace State
{
    Running::Running()
        : mStart{std::chrono::system_clock::now()}
    {
    }

    Running::Running(const std::string_view &xIn)
        : mStart{std::chrono::system_clock::now()}, mAddInfos{xIn}
    {
    }
    bool Running::Apply(StateMachine &xStateMachine, const Command &xIn) noexcept
    {
        try
        {
            if (xIn.GetType() != CommandType::Stop)
                throw std::runtime_error("Wrong CommandType, expected stop command");

            LogData tDTO;
            tDTO.description = mAddInfos;
            tDTO.start = mStart;
            tDTO.end = std::chrono::system_clock::now();
            tDTO.duration = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(tDTO.end - mStart).count());

            std::shared_ptr<Start> tNewState = std::make_shared<Start>();
            xStateMachine.SetSate(tNewState);

            if (!Database::write(tDTO))
                throw std::runtime_error("Can't write data to db.");

            return true;
        }
        catch (...)
        {
            Exception::handle();
            return false;
        }
    }

    void Running::StartTimer() noexcept
    {
        mStart = std::chrono::system_clock::now();
    }
} // namespace State
