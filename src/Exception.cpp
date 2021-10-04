//
//  Exception.cpp
//  WorkTimer
//
//  Created by Nils Brödner on 01.10.21.
//

#include "Exception.h"
#include "Logger.h"

#include <iostream>

namespace Exception
{
    void handle() noexcept
    {
        try
        {
            throw;
        }
        catch (const std::exception &e)
        {
            Logger::getInstance().getLogger()->error(e.what());
            Logger::getInstance().getLogger()->flush();
        }
        catch (...)
        {
            Logger::getInstance().getLogger()->error("Unknown Exception.");
            Logger::getInstance().getLogger()->flush();
        }
    }
}
