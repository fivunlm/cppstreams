//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <iostream>
#include <list>
#include "../../src/cppstreams.cpp"


#include <gtest/gtest.h>


int main(int ac, char *av[]) {
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}