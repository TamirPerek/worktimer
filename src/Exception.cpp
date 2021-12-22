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

    vdk::signal<void(std::string)> gExceptionSignal;

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
            getExceptionSignal().emit("Error occurred.");
        }
        catch (const DumpException &e)
        {
            Logger::getInstance().getLogger()->error("DumpException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
            getExceptionSignal().emit("Error occurred.");
        }
        catch (const DatabaseException &e)
        {
            Logger::getInstance().getLogger()->error("DatabaseException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
            getExceptionSignal().emit("Error occurred.");
        }
        catch (const UIException &e)
        {
            Logger::getInstance().getLogger()->error("UIException: {}", e.what());
            Logger::getInstance().getLogger()->flush();
            getExceptionSignal().emit("Error occurred.");
        }
        catch (const std::exception &e)
        {
            Logger::getInstance().getLogger()->error(e.what());
            Logger::getInstance().getLogger()->flush();
            getExceptionSignal().emit("Error occurred.");
        }
        catch (...)
        {
            Logger::getInstance().getLogger()->error("Unknown Exception.");
            Logger::getInstance().getLogger()->flush();
            getExceptionSignal().emit("Error occurred.");
        }
    }

    vdk::signal<void(std::string)> &getExceptionSignal()
    {
        return gExceptionSignal;
    }
}
