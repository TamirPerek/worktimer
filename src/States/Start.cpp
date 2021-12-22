#include "Start.h"

#include "Running.h"

#include "../Command.h"
#include "../Exception.h"
#include "../StateMachine.h"
#include "../Database.h"
#include "../LogDataDTO.h"

#include <iostream>
#include <chrono>

namespace State
{
    bool Start::Apply(StateMachine &xStateMachine, Command &&xIn) noexcept
    {
        try
        {
            if (xIn.GetType() != CommandType::Start)
                THROWSTATE("Wrong CommandType, expected {} command", "Start");

            LogData tDTO;
            tDTO.description = xIn.GetAddInfos();
            tDTO.start = std::chrono::system_clock::now();
            tDTO.end = std::chrono::system_clock::now();
            tDTO.duration = 0;
            tDTO.category = xIn.GetCategory();

            if (tDTO.id = Database::insert(tDTO); tDTO.id <= 0)
                THROWSTATE("Can't write data to db: {}", tDTO.description);

            auto tNextState = std::make_unique<Running>(xIn.GetAddInfos(), xIn.GetCategory());
            tNextState->setDatabaseID(tDTO.id);
            xStateMachine.SetSate(std::move(tNextState));

            return true;
        }
        catch (...)
        {
            Exception::handle();
            return false;
        }
    }
} // namespace State
