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
    bool Running::Apply(StateMachine &xStateMachine, Command &&xIn) noexcept
    {
        try
        {
            if (xIn.GetType() != CommandType::Stop)
                THROWSTATE("Wrong CommandType, expected {} command", "Stop");

            LogData tDTO;
            tDTO.description = mAddInfos;
            tDTO.start = mStart;
            tDTO.end = std::chrono::system_clock::now();
            tDTO.duration = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(tDTO.end - mStart).count());

            xStateMachine.SetSate(std::make_unique<Start>());

            if (!Database::write(tDTO))
                THROWSTATE("Can't write data to db: {}", tDTO.description);

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
