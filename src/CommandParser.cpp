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

        if (const std::regex tRegex{R"(^-[sS][tT][aA][rR][tT].*)"}; std::regex_match(tCompleteCommand, tRegex))
            return Command{CommandType::Start, tCommand};

        if (const std::regex tRegex{R"(^-[sS][tT][oO][pP].*)"}; std::regex_match(tCompleteCommand, tRegex))
            return Command{CommandType::Stop};

        if (const std::regex tRegex{R"(^-[eE][xX][iI][tT].*)"}; std::regex_match(tCompleteCommand, tRegex))
            exit(EXIT_SUCCESS);

        if (const std::regex tRegex{R"(^-[sS][tT][aA][tT][uU][sS].*)"}; std::regex_match(tCompleteCommand, tRegex))
            return Command{CommandType::Status};

        return Command{CommandType::Error, tCompleteCommand};
    }
    catch (...)
    {
        Exception::handle();
        return Command{CommandType::Error, tCompleteCommand};
    }
}
