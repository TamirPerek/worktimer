file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.hpp" "./*.h")

add_executable(${This} ${TARGET_SRC})

target_link_libraries(${This}
                     sqlite3
                     spdlog   
)