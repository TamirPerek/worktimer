
#include <string>
#include <filesystem>

namespace StaticData
{
    constexpr std::string_view pathToDB = R"(db/worktimer.db)";

    #ifdef __APPLE__
    const std::filesystem::path pathToResource{std::filesystem::current_path() / "WorkTimer.app/Contents/MacOS/"};
#else
    const std::filesystem::path pathToResource{std::filesystem::current_path()};
#endif 
} // namespace StaticData
