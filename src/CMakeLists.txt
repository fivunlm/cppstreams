set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(CPPSTREAMS_SOURCE_FILES cppstreams.cpp)

add_library(cppstreams_lib STATIC ${CPPSTREAMS_SOURCE_FILES})