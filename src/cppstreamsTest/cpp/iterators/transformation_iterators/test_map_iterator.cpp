//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include <string>

#include "utilities.h"

#include "cppstreams/iterator.h"

using cppstreams::iterators::transformation_iterators::map_iterator;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Iterator_TransformationInterator_MapIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( values ) );

	map_iterator<int, int> filter_it1( it, negator );
	map_iterator<int, std::string> filter_it2( it, to_string );

	map_iterator<int, int> filter_it3( const_it, negator );
	map_iterator<int, std::string> filter_it4( const_it, to_string );
}

TEST( Iterator_TransformationInterator_MapIterator, IteratingSameType ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	map_iterator<int, int> map_it( it, negator );

	for ( int i = 1; i <= 7; ++i ) {
		EXPECT_TRUE( map_it.has_element() );

		EXPECT_EQ( map_it.peek(), -i );
		EXPECT_EQ( map_it.fetch(), -i );
	}

	EXPECT_FALSE( map_it.has_element() );

	EXPECT_THROW( map_it.peek(), std::range_error );
	EXPECT_THROW( map_it.fetch(), std::range_error );
}

TEST( Iterator_TransformationInterator_MapIterator, IteratingDifferentType ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	map_iterator<int, std::string> map_it( it, to_string );

	for ( int i = 1; i <= 7; ++i ) {
		EXPECT_TRUE( map_it.has_element() );

		EXPECT_EQ( map_it.peek(), std::to_string( i ) );
		EXPECT_EQ( map_it.fetch(), std::to_string( i ) );
	}

	EXPECT_FALSE( map_it.has_element() );

	EXPECT_THROW( map_it.peek(), std::range_error );
	EXPECT_THROW( map_it.fetch(), std::range_error );
}
