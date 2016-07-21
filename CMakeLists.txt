cmake_minimum_required(VERSION 3.5)
project(cppstreams)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp streams/Stream.h)
add_executable(cppstreams ${SOURCE_FILES} streams/Stream.h)