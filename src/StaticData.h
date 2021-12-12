
#include <string>
#include <filesystem>

namespace StaticData
{
    constexpr std::string_view pathToDB = R"(db/worktimer.db)";

#if defined(__APPLE__) && (!defined(NDEBUG) || !defined(DEBUG))
    const std::filesystem::path pathToResource{"../Resources/" /* std::filesystem::current_path()/ "WorkTimer.app/Contents/MacOS/"*/};
#else
    const std::filesystem::path pathToResource{std::filesystem::current_path()};
#endif 
} // namespace StaticData
