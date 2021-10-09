set(This sqlite3)

file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.c" "./*.hpp" "./*.h")

add_library(${This} STATIC ${TARGET_SRC})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

target_link_libraries(${This} Threads::Threads)