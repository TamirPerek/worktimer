file(GLOB_RECURSE TARGET_SRC "*.cpp" "*.hpp" "*.h")

foreach(FILE ${TARGET_SRC}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    # Group into "Source Files" and "Header Files"
    set(GROUP "${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

if(MSVC)
add_executable(${This} WIN32 ${TARGET_SRC})
else()
add_executable(${This} ${TARGET_SRC})
endif()

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