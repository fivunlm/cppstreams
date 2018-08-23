//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <list>

#include <gtest/gtest.h>

#include "cppstreams.h"

using ::testing::Test;
using namespace std;


class StreamsFromListTests : public Test {

protected:

    StreamsFromListTests() {
    }

    virtual ~StreamsFromListTests() {}

};

TEST_F(StreamsFromListTests, StreamsFromListTests_MapDoesNotChangeListSize_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> resultList = Stream<int, std::list<int> >::makeStream(testList)
            .map([](const int &iValue) { return iValue * 2; })
            .collect();
    ASSERT_EQ(resultList.size(), testList.size());
}

TEST_F(StreamsFromListTests, StreamsFromListTests_MapLambdaWorks_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> resultList = Stream<int, std::list<int> >::makeStream(testList)
            .map([](const int &iValue) { return iValue * 2; })
            .collect();

    ASSERT_EQ(resultList.size(), 10);

    ASSERT_EQ(resultList.front(), 0);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 2);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 4);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 6);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 8);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 10);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 12);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 14);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 16);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 18);
    resultList.pop_front();
}


TEST_F(StreamsFromListTests, StreamsFromListTests_FilterWorks_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> resultList = Stream<int, std::list<int> >::makeStream(testList)
            .filter([](const int &iValue) { return iValue % 2 == 0; })
            .collect();

    ASSERT_EQ(resultList.size(), 5);

    ASSERT_EQ(resultList.front(), 0);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 2);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 4);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 6);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 8);
    resultList.pop_front();
}


TEST_F(StreamsFromListTests, StreamsFromListTests_CollectLimitWorks_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> resultList = Stream<int, std::list<int> >::makeStream(testList)
            .collect(5);

    ASSERT_EQ(resultList.size(), 5);

    ASSERT_EQ(resultList.front(), 0);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 1);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 2);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 3);
    resultList.pop_front();
    ASSERT_EQ(resultList.front(), 4);
    resultList.pop_front();
}

TEST_F(StreamsFromListTests, StreamsFromListTests_SumAlistOfIntegers_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = Stream<int, std::list<int> >::makeStream(testList)
            .sum();

    ASSERT_EQ(sum, 45);
}

TEST_F(StreamsFromListTests, StreamsFromListTests_FindFirst_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::list<int> >::makeStream(testList)
            .findFirst([](int i) { return i > 0 && i % 2 == 0; }, 0);

    ASSERT_EQ(result, 2);
}

TEST_F(StreamsFromListTests, StreamsFromListTests_FindFirstReturnDefaultValue_Test) {
    std::list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::list<int> >::makeStream(testList)
            .findFirst([](int i) { return i > 100; }, 0);

    ASSERT_EQ(result, 0);
}

TEST_F(StreamsFromListTests, StreamsFromListTests_SumAfterMap_Test) {
    list<int> testList{0, 1, 2};
    int result = Stream<int, std::list<int> >::makeStream(testList)
            .map([](const int &value) { return value * 2; })
            .sum(0);

    ASSERT_EQ(result, 6);
}

TEST_F(StreamsFromListTests, StreamsFromListTests_SumAfterFilter_Test) {
    list<int> testList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::list<int> >::makeStream(testList)
            .filter([](const int & iValue) { return iValue % 2 == 0; } )
            .sum(0);

    ASSERT_EQ(result, 20);
}