cmake_minimum_required(VERSION 3.0.0)

project(cppstreams_lib VERSION 1.0.0 LANGUAGES CXX)

option(CPPSTREAMS_BuildTests "Build the unit tests" ON)

#set(CMAKE_VERBOSE_MAKEFILE OFF)
#set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CPPSTREAMS_SOURCE_DIR   "src/")

add_library(${PROJECT_NAME} INTERFACE)

if(CPPSTREAMS_BuildTests)
    enable_testing()
    include_directories(${CPPSTREAMS_SOURCE_DIR})
    add_subdirectory(tests)
endif()
