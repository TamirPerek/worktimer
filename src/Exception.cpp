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
        catch (const StateException &e)
        {
            Logger::getInstance().getLogger()->error("StateException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
        }
        catch (const DumpException &e)
        {
            Logger::getInstance().getLogger()->error("DumpException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
        }
        catch (const DatabaseException &e)
        {
            Logger::getInstance().getLogger()->error("DatabaseException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
        }
        catch (const UIException &e)
        {
            Logger::getInstance().getLogger()->error("UIException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
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
