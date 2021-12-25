#include "Dump.h"

#include "Exception.h"
#include "Database.h"

#include <fstream>
#include <vector>

#include <wx/datetime.h>

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

int Dump::DumpCallback(void *xOutputStream, int xCount, char **xData, [[maybe_unused]] char **xColumns)
{
    try
    {
        if (!xOutputStream)
            THROWDUMP("Path is empty. {}", "");

        std::vector<std::string> tData;
        for (int i = 0; i < xCount; i++)
        {
            const std::string tColumn = xColumns[i];
            if (/*tColumn == "id" || */tColumn == "categories.id")
                continue;

            if (tColumn == "start" || tColumn == "end")
                tData.push_back(TimeToString(std::stol(xData[i])));
            else
                tData.push_back(xData[i]);
        }

        const auto tOutputStream = static_cast<std::ofstream *>(xOutputStream);

        *tOutputStream << fmt::format("{}\n", fmt::join(tData, ";"));

        return EXIT_SUCCESS;
    }
    catch (...)
    {
        Exception::handle();
        return EXIT_FAILURE;
    }
}

std::string Dump::TimeToString(const time_t &xIn) noexcept
{
    wxDateTime tTime;
    tTime.Set(xIn);

    return tTime.Format("%Y-%m-%d %T").ToStdString();
}