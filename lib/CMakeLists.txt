include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(sqlite3 URL "https://sqlite.org/2020/sqlite-amalgamation-3320300.zip")
if (NOT sqlite3_POPULATED)
  # notice that we do not call `add_subdirectory`, we simply fetch and then
  # use the subdirectory sources directly.
  FetchContent_Populate(sqlite3)
endif()

#===== Fetch spdlog as archive ====================#
FetchContent_Declare(
    spdlog
    URL       "https://github.com/gabime/spdlog/archive/v1.3.1.zip"
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    set(SPDLOG_BUILD_EXAMPLES OFF)
    set(SPDLOG_BUILD_BENCH    OFF)
    set(SPDLOG_BUILD_TESTS    OFF)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()
