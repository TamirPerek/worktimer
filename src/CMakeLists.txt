file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.hpp" "./*.h")

add_executable(${This} ${TARGET_SRC})

target_link_libraries(${This}
                     sqlite3
                     spdlog  
                     wxbase
                     wxcore
                     wxnet
)
add_custom_command(
        TARGET ${This} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/db/worktimer.db
                ${CMAKE_CURRENT_BINARY_DIR}/db/worktimer.db)