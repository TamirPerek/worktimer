set(THIS WorkTimer_Test)

file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.hpp" "./*.h")

add_executable(${THIS} ${TARGET_SRC})

target_link_libraries(${THIS}
                        gtest_main
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)