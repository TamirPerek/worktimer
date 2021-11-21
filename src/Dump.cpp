#include "Dump.h"

#include "Exception.h"
#include "Database.h"

#include <fstream>
#include <string>
#include <vector>

void Dump::DumpDatabase(const std::filesystem::path &xPath) noexcept
{
    try
    {
        if (!std::filesystem::exists(xPath.parent_path()) && !std::filesystem::create_directories(xPath.parent_path()))
            THROWDUMP("Can't create directories {}", xPath.string());

        std::ofstream tOutpoutStream{xPath};

        if (!tOutpoutStream.is_open())
            THROWDUMP("Can't open file: {}", xPath.string());

        if (!Database::read(&Dump::DumpCallback, &tOutpoutStream))
            THROWDUMP("Can't read data from database to file: {}", xPath.string());
    }
    catch (...)
    {
        Exception::handle();
    }
}

int Dump::DumpCallback(void *xOutpoutStream, int xCount, char **xData, [[maybe_unused]] char **xColumns)
{
    try
    {
        if (!xOutpoutStream)
            THROWDUMP("Path is empty. {}", "");

        std::vector<std::string> tData;
        for (int i = 0; i < xCount; i++)
        {
            tData.push_back(xData[i]);
        }

        const auto tOutpoutStream = static_cast<std::ofstream *>(xOutpoutStream);

        *tOutpoutStream << fmt::format("{}\n", fmt::join(tData, ";"));

        return EXIT_SUCCESS;
    }
    catch (...)
    {
        Exception::handle();
        return EXIT_FAILURE;
    }
}