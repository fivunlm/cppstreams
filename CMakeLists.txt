cmake_minimum_required(VERSION 3.5)
project(cppstreams_lib CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# Google Tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# CPPSTREAMS LIB
add_subdirectory(src)

# MAIN
include_directories(src)
set(SOURCE_FILES main.cpp tests/streams_from_list_tests.cpp)
add_executable(main ${SOURCE_FILES})
target_link_libraries(main cppstreams gtest gtest_main)

add_test(
        NAME main
        COMMAND main
)