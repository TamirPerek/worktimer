set(This sqlite3)

set(CMAKE_CXX_LI "-ldl")

file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.c" "./*.hpp" "./*.h")

add_library(${This} STATIC ${TARGET_SRC})
