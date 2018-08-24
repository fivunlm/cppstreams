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

#include <map>
#include <unordered_map>

#include "cppstreams/iterators/container_iterator.h"

template<class T>
using container_iterator = cppstreams::iterators::container_iterator<T>;

std::vector<int> vector( { 1, 2, 3 } );
const std::vector<int> const_vector( { 1, 2, 3 } );

#define values { 3, 7, 5, 1, 3, -5 }
#define map_values { {3, 1}, {7, 2}, {5, 3}, {1, 4}, {3, 5}, {-5, 6} }

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
		EXPECT_TRUE( it.has_next() );
		EXPECT_TRUE( const_it.has_next() );

		EXPECT_EQ( it.peek(), i );
		EXPECT_EQ( it.next(), i );
		EXPECT_EQ( const_it.peek(), i );
		EXPECT_EQ( const_it.next(), i );
	}

	EXPECT_FALSE( it.has_next() );
	EXPECT_FALSE( const_it.has_next() );
}

template<class T>
void container_test_unsorted() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void container_test_unordered() {
	T container { values };
	container_iterator<T> it( container );

	std::multiset<int> comparator { values };
	std::multiset<int>::iterator found;

	for ( int i = 0; i < 6; ++i ) {
		EXPECT_TRUE( it.has_next() );
		found = comparator.find( it.next() );
		EXPECT_NE( found, comparator.end() );
		comparator.erase( found );
	}

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void container_test_unordered_deduplicated() {
	T container { values };
	container_iterator<T> it( container );

	std::set<int> comparator { values };
	std::set<int>::iterator found;

	for ( int i = 0; i < 5; ++i ) {
		EXPECT_TRUE( it.has_next() );
		found = comparator.find( it.next() );
		EXPECT_NE( found, comparator.end() );
		comparator.erase( found );
	}

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void container_test_sorted() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void container_test_sorted_deduplicated() {
	T container { values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), -5 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 1 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 3 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 5 );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), 7 );

	EXPECT_FALSE( it.has_next() );
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
	container_test_unordered_deduplicated<std::unordered_set<int> >();
}

TEST( Iterator_ContainerIterator, UnorderedMultiset ) {
	container_test_unordered<std::unordered_multiset<int> >();
}

TEST( Iterator_ContainerIterator, Vector ) {
	container_test_unsorted<std::vector<int> >();
}

template<class T>
void map_test_sorted() {
	T container { map_values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( -5, 6 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 1, 4 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 3, 1 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 3, 5 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 5, 3 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 7, 2 )) );

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void map_test_sorted_deduplicated() {
	T container { map_values };
	container_iterator<T> it( container );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( -5, 6 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 1, 4 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 3, 1 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 5, 3 )) );

	EXPECT_TRUE( it.has_next() );
	EXPECT_EQ( it.next(), (std::pair<const int, int>( 7, 2 )) );

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void map_test_unordered() {
	T container { map_values };
	container_iterator<T> it( container );

	std::multimap<int, int> comparator { map_values };
	std::multimap<int, int>::iterator found;

	for ( int i = 0; i < 6; ++i ) {
		EXPECT_TRUE( it.has_next() );
		found = comparator.find( it.next().first );
		EXPECT_NE( found, comparator.end() );
		comparator.erase( found );
	}

	EXPECT_FALSE( it.has_next() );
}

template<class T>
void map_test_unordered_deduplicated() {
	T container { map_values };
	container_iterator<T> it( container );

	std::map<int, int> comparator { map_values };
	std::map<int, int>::iterator found;

	for ( int i = 0; i < 5; ++i ) {
		EXPECT_TRUE( it.has_next() );
		found = comparator.find( it.next().first );
		EXPECT_NE( found, comparator.end() );
		comparator.erase( found );
	}

	EXPECT_FALSE( it.has_next() );
}

TEST( Iterator_ContainerIterator, Map ) {
	map_test_sorted_deduplicated<std::map<int, int> >();
}

TEST( Iterator_ContainerIterator, Multimap ) {
	map_test_sorted<std::multimap<int, int> >();
}

TEST( Iterator_ContainerIterator, UnorderedMap ) {
	map_test_unordered_deduplicated<std::unordered_map<int, int> >();
}

TEST( Iterator_ContainerIterator, UnorderedMultimap ) {
	map_test_unordered<std::unordered_multimap<int, int> >();
}
