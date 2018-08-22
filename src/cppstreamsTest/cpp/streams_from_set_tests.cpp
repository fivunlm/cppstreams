//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <set>

#include <gtest/gtest.h>

#include "cppstreams.h"

using ::testing::Test;
using namespace std;


class StreamsFromSetTests : public Test {

protected:

    StreamsFromSetTests() {}

    virtual ~StreamsFromSetTests() {}

};

TEST_F(StreamsFromSetTests, StreamsFromSetTests_MapDoesNotChangeSetSize_Test) {
    set<int> testSet{0, 1, 2};
    std::set<int> resultSet = Stream<int, std::set<int> >::makeStream(testSet)
            .map([](const int &value) { return value * 2; })
            .collect();
    ASSERT_EQ(resultSet.size(), testSet.size());
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_MapLambdaWorks_Test) {
    set<int> testSet{0, 1, 2};
    std::set<int> resultSet = Stream<int, std::set<int> >::makeStream(testSet)
            .map([](const int &value) { return value * 2; })
            .collect();

    auto it = resultSet.begin();

    ASSERT_EQ(*it++, 0);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it, 4);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_FilterWorks_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std:set<int> resultSet = Stream<int, std::set<int> >::makeStream(testSet)
        .filter([](const int & iValue) { return iValue % 2 == 0; } )
        .collect();

    ASSERT_EQ(resultSet.size(), 5);

    auto it = resultSet.begin();

    ASSERT_EQ(*it++, 0);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it++, 6);
    ASSERT_EQ(*it, 8);

}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_CollectLimitWorks_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std:set<int> resultSet = Stream<int, std::set<int> >::makeStream(testSet)
        .collect(5);

    ASSERT_EQ(resultSet.size(), 5);

    auto it = resultSet.begin();

    ASSERT_EQ(*it++, 0);
    ASSERT_EQ(*it++, 1);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it++, 3);
    ASSERT_EQ(*it, 4);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_SumASetOfIntegers_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = Stream<int, std::set<int> >::makeStream(testSet)
            .sum();

    ASSERT_EQ(sum, 45);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_FindFirst_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::set<int> >::makeStream(testSet)
            .findFirst([] (const int& i) { return i > 0 && i % 2 == 0; }, 0);

    ASSERT_EQ(result, 2);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_FindFirstReturnDefault_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::set<int> >::makeStream(testSet)
            .findFirst([] (const int& i) { return i > 100; }, 0);

    ASSERT_EQ(result, 0);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_SumAfterMap_Test) {
    set<int> testSet{0, 1, 2};
    int result = Stream<int, std::set<int> >::makeStream(testSet)
            .map([](const int &value) { return value * 2; })
            .sum(0);

    ASSERT_EQ(result, 6);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_SumAfterFilter_Test) {
    set<int> testSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int result = Stream<int, std::set<int> >::makeStream(testSet)
        .filter([](const int & iValue) { return iValue % 2 == 0; } )
        .sum(0);

    ASSERT_EQ(result, 20);
}

TEST_F(StreamsFromSetTests, StreamsFromSetTests_ResultSetIsOrdered_Test) {
    set<int> testSet{0, 1, 2, 3, 4};
    std:set<int> resultSet = Stream<int, std::set<int> >::makeStream(testSet)
        .map([](const int& i) { return 100 - i;})
        .collect();

    ASSERT_EQ(resultSet.size(), 5);

    auto it = resultSet.begin();

    ASSERT_EQ(*it++, 96);
    ASSERT_EQ(*it++, 97);
    ASSERT_EQ(*it++, 98);
    ASSERT_EQ(*it++, 99);
    ASSERT_EQ(*it, 100);
}