#include "Running.h"

#include "Stop.h"

#include "../Command.h"
#include "../Exception.h"
#include "../StateMachine.h"

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
            // std::cout << "Running " << xIn.GetAddInfos() << "\n";

            if (xIn.GetType() != CommandType::Stop)
                throw std::runtime_error(std::string{"Wrong CommandType, expected stop command"});

            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - mStart;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::time_t start_time = std::chrono::system_clock::to_time_t(mStart);
            std::string tEndTime{std::ctime(&end_time), 24};
            std::string tStartTime{std::ctime(&start_time), 24};

            std::shared_ptr<Stop> tNewState = std::make_shared<Stop>(xStateMachine, fmt::format("{}; {}; {}; {};",
                                                                                                tStartTime,
                                                                                                tEndTime,
                                                                                                mAddInfos,
                                                                                                elapsed_seconds.count() / 60));

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
