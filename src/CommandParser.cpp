#include "CommandParser.h"

#include "Exception.h"

#include <iostream>
#include <regex>

Command CommandParser::read() const noexcept
{
    std::string tCompleteCommand;
    try
    {
        std::getline(std::cin, tCompleteCommand);

        const auto tPos = tCompleteCommand.find_first_of(' ');

        std::string tCommand;
        if (tPos != std::string::npos)
            tCommand = tCompleteCommand.substr(tPos + 1);

        if (std::regex tStart{R"(^-[sS][tT][aA][rR][tT].*)"}; std::regex_match(tCompleteCommand, tStart))
            return Command{CommandType::Start, tCommand};

        if (std::regex tStart{R"(^-[sS][tT][oO][pP].*)"}; std::regex_match(tCompleteCommand, tStart))
            return Command{CommandType::Stop, tCommand};

        if (std::regex tStart{R"(^-[eE][xX][iI][tT].*)"}; std::regex_match(tCompleteCommand, tStart))
            exit(EXIT_SUCCESS);

        return Command{CommandType::Error, tCompleteCommand};
    }
    catch (...)
    {
        Exception::handle();
        return Command{CommandType::Error, tCompleteCommand};
    }
}
