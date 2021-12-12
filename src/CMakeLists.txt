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

if(APPLE)
    set(CUR_TARGET worktimer)        
    # NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
    # the property added to Info.plist
    set(MACOSX_BUNDLE_ICON_FILE worktimer.icns)

    # And this part tells CMake where to find and install the file itself
    set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/../images/worktimer.icns)
    set_source_files_properties(${myApp_ICON} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    # Copy DB File
    set(DB_FILE ${CMAKE_SOURCE_DIR}/db/worktimer.db)
    # target_sources(target PRIVATE ${DB_FILE})
    set_source_files_properties(
    ${DB_FILE}
    PROPERTIES
        MACOSX_PACKAGE_LOCATION MacOS/db
    )

    add_executable(${This} MACOSX_BUNDLE ${myApp_ICON} ${TARGET_SRC} ${DB_FILE})  

    set_target_properties(${This} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${This}
        MACOSX_BUNDLE_BUNDLE_NAME ${This}
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}"
        MACOSX_PACKAGE_LOCATION MacOSX
     )
elseif(MSVC)
    add_executable(${This} WIN32 ${TARGET_SRC} resource.rc)

    add_custom_command(
            TARGET ${This} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_SOURCE_DIR}/db/worktimer.db
                    ${CMAKE_CURRENT_BINARY_DIR}/db/worktimer.db)
else()
    add_executable(${This} ${TARGET_SRC})

    add_custom_command(
            TARGET ${This} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_SOURCE_DIR}/db/worktimer.db
                    ${CMAKE_CURRENT_BINARY_DIR}/db/worktimer.db)
endif()

target_link_libraries(${This}
                     sqlite3
                     spdlog  
                     wxbase
                     wxcore
                     wxnet
                     signals
)