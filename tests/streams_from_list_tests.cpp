//
// Created by FernandoDamian on 9/1/2016.
//
#include <cppstreams.h>
#include <gtest/gtest.h>
#include <list>

using ::testing::Test;
using namespace std;


class StreamsFromListTests : public Test {

protected:

    StreamsFromListTests() {
        initList();
    }

    virtual ~StreamsFromListTests() {}

    void initList() {
        m_lTestList.push_back(0);
        m_lTestList.push_back(1);
        m_lTestList.push_back(2);
        m_lTestList.push_back(3);
        m_lTestList.push_back(4);
        m_lTestList.push_back(5);
        m_lTestList.push_back(6);
        m_lTestList.push_back(7);
        m_lTestList.push_back(8);
        m_lTestList.push_back(9);
    }

    list<int> m_lTestList;

};

TEST_F(StreamsFromListTests, StreamsFromListTests_MapDoesNotChangeListSize_Test) {
    std::list<int> lResult = Stream<int>::makeStream(m_lTestList)
            .map([](const int &iValue) { return iValue * 2; })
            .collect();
    ASSERT_EQ(lResult.size(), m_lTestList.size());
}

TEST_F(StreamsFromListTests, StreamsFromListTests_MapLambdaWorks_Test) {
    std::list<int> lResult = Stream<int>::makeStream(m_lTestList)
            .map([](const int &iValue) { return iValue * 2; })
            .collect();

    ASSERT_EQ(lResult.size(), 10);

    ASSERT_EQ(lResult.front(), 0);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 2);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 4);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 6);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 8);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 10);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 12);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 14);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 16);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 18);
    lResult.pop_front();
}


TEST_F(StreamsFromListTests, StreamsFromListTests_FilterWorks_Test) {
    std:list<int> lResult = Stream<int>::makeStream(m_lTestList)
        .filter([](const int & iValue) { return iValue % 2 == 0; } )
        .collect();

    ASSERT_EQ(lResult.size(), 5);

    ASSERT_EQ(lResult.front(), 0);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 2);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 4);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 6);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 8);
    lResult.pop_front();
}


TEST_F(StreamsFromListTests, StreamsFromListTests_CollectLimitWorks_Test) {
    std:list<int> lResult = Stream<int>::makeStream(m_lTestList)
        .collect(5);

    ASSERT_EQ(lResult.size(), 5);

    ASSERT_EQ(lResult.front(), 0);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 1);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 2);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 3);
    lResult.pop_front();
    ASSERT_EQ(lResult.front(), 4);
    lResult.pop_front();
}

TEST_F(StreamsFromListTests, StreamsFromListTests_SumAlistOfIntegers_Test) {
    int iResult = Stream<int>::makeStream(m_lTestList)
        .sum();

    ASSERT_EQ(iResult, 45);
}
