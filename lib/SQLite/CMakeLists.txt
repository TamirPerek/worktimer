set(This sqlite3)

file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.c" "./*.hpp" "./*.h")

add_library(${This} STATIC ${TARGET_SRC})