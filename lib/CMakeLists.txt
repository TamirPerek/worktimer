# ------------------ Googletest ------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ------------------ SQLite3 ------------------
# FetchContent_Declare(sqlite3 URL "https://www.sqlite.org/2021/sqlite-amalgamation-3360000.zip")
# if (NOT sqlite3_POPULATED)
#   # notice that we do not call `add_subdirectory`, we simply fetch and then
#   # use the subdirectory sources directly.
#   FetchContent_Populate(sqlite3)
# endif()

add_subdirectory(SQLite)

# ------------------ Fetch spdlog as archive ------------------
FetchContent_Declare(
    spdlog
    URL       "https://github.com/gabime/spdlog/archive/refs/tags/v1.9.2.zip"
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    set(SPDLOG_BUILD_EXAMPLES OFF)
    set(SPDLOG_BUILD_BENCH    OFF)
    set(SPDLOG_BUILD_TESTS    OFF)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

# ------------------ wxWidgets ------------------
set(wxBUILD_SHARED OFF CACHE BOOL "Build wx libraries as shared libs")
set(wxBUILD_PRECOMP OFF CACHE BOOL "Use precompiled headers")
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "Build a single library")
set(wxUSE_STL ON CACHE BOOL "use C++ STL classes")
set(wxUSE_RC_MANIFEST ON CACHE BOOL "")

FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.1.5
)

# ------------------ vdkSignals ------------------
FetchContent_Declare(
  signals
  GIT_REPOSITORY https://github.com/TamirPerek/signals.git
)
set(SIGNALS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SIGNALS_BUILD_DEMO OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(wxWidgets signals)