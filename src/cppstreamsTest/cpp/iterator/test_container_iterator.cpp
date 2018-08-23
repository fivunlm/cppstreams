//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

#include "cppstreams/iterators/container_iterator.h"

template<class T>
using container_iterator = cppstreams::iterators::container_iterator<T>;

std::vector<int> vector( { 1, 2, 3 } );
const std::vector<int> const_vector( { 1, 2, 3 } );

#define values { 3, 7, 5, 1, 3, -5 }

TEST( Iterator_ContainerIterator, Constructors ) {
	EXPECT_NO_THROW( container_iterator<std::vector<int>> it( vector ) );
	EXPECT_NO_THROW( container_iterator<std::vector<int>> it( vector.begin(), vector.begin() + 3 ) );

	EXPECT_NO_THROW( container_iterator<std::vector<int>> it( const_vector ) );
	EXPECT_NO_THROW( container_iterator<std::vector<int>> it( const_vector.begin(), const_vector.begin() + 3 ) );
}

TEST( Iterator_ContainerIterator, Iterating ) {
	container_iterator<std::vector<int>> it( vector );
	container_iterator<std::vector<int>> const_it( const_vector );

	for ( int i = 1; i <= 3; ++i ) {
		EXPECT_TRUE( it.hasNext() );
		EXPECT_TRUE( const_it.hasNext() );

		EXPECT_EQ( it.next(), i );
		EXPECT_EQ( const_it.next(), i );
	}

	EXPECT_FALSE( it.hasNext() );
	EXPECT_FALSE( const_it.hasNext() );
}

template<class T>
void container_test_unsorted() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_FALSE( it.hasNext() );
}

template<class T>
void container_test_unsorted_deduplicated() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_FALSE( it.hasNext() );
}

template<class T>
void container_test_unsorted_grouped() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_FALSE( it.hasNext() );
}

template<class T>
void container_test_sorted() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_FALSE( it.hasNext() );
}

template<class T>
void container_test_sorted_deduplicated() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 3);

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.hasNext() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_FALSE( it.hasNext() );
}

TEST( Iterator_ContainerIterator, Array ) {
	container_test_unsorted<std::array<int, 6> >();
}

TEST( Iterator_ContainerIterator, Deque ) {
	container_test_unsorted<std::deque<int> >();
}

TEST( Iterator_ContainerIterator, ForwardList ) {
	container_test_unsorted<std::forward_list<int> >();
}

TEST( Iterator_ContainerIterator, List ) {
	container_test_unsorted<std::list<int> >();
}

TEST( Iterator_ContainerIterator, Set ) {
	container_test_sorted_deduplicated<std::set<int> >();
}

TEST( Iterator_ContainerIterator, Multiset ) {
	container_test_sorted<std::multiset<int> >();
}

TEST( Iterator_ContainerIterator, UnorderedSet ) {
	container_test_unsorted_deduplicated<std::unordered_set<int> >();
}

TEST( Iterator_ContainerIterator, UnorderedMultiset ) {
	container_test_unsorted_grouped<std::unordered_multiset<int> >();
}

TEST( Iterator_ContainerIterator, Vector ) {
	container_test_unsorted<std::vector<int> >();
}

// TODO: Implement tests for maps

