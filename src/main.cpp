#include "Exception.h"
#include "StateMachine.h"
#include "CommandParser.h"

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try
    {
        StateMachine tStates;
        CommandParser tParser;
        while(1)
        {
            tStates.Apply(tParser.read());
        }
        return EXIT_SUCCESS;
    }
    catch (const std::exception &e)
    {
        Exception::handle();
        return EXIT_FAILURE;
    }
}
