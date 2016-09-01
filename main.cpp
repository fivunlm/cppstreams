#include <iostream>
#include <list>
#include "src/cppstreams.cpp"


#include <gtest/gtest.h>


int main(int ac, char *av[]) {
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}