add_subdirectory(thirdparty/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CPPSTREAMS_UNITTEST_TARGET_NAME "cppstreams_unit")

add_executable(${CPPSTREAMS_UNITTEST_TARGET_NAME}
        "../src/cppstreams.cpp"
        "src/main.cpp"
        "src/streams_from_list_tests.cpp"
        "src/streams_from_vector_tests.cpp"
        "src/streams_from_set_tests.cpp"
        )

set_target_properties(${CPPSTREAMS_UNITTEST_TARGET_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(${CPPSTREAMS_UNITTEST_TARGET_NAME} gtest gtest_main)

add_test(NAME ${CPPSTREAMS_UNITTEST_TARGET_NAME}_all COMMAND ${CPPSTREAMS_UNITTEST_TARGET_NAME})
