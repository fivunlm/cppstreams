//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "cppstreams/iterator.h"

using cppstreams::iterators::array_iterator;

int array[] = { 1, 2, 3 };
constexpr int const_array[] = { 1, 2, 3 };

TEST( Iterator_ArrayIterator, Constructors ) {
	EXPECT_NO_THROW( array_iterator<int> it( array ) );
	EXPECT_NO_THROW( array_iterator<int> it( array, array + 3 ) );

	EXPECT_NO_THROW( array_iterator<int> it( const_array ) );
	EXPECT_NO_THROW( array_iterator<int> it( const_array, const_array + 3 ) );
}

TEST( Iterator_ArrayIterator, ConvinienceMethods ) {
	EXPECT_NO_THROW( cppstreams::get_iterator( array ) );
	EXPECT_NO_THROW( cppstreams::get_iterator<int>( array, array + 3 ) );

	EXPECT_NO_THROW( cppstreams::get_iterator( const_array ) );
	EXPECT_NO_THROW( cppstreams::get_iterator<int>( const_array, const_array + 3 ) );
}

TEST( Iterator_ArrayIterator, Iterating ) {
	array_iterator<int> it( array );
	array_iterator<int> const_it( const_array );

	for ( int i = 1; i <= 3; ++i ) {
		EXPECT_TRUE( it.has_element() );
		EXPECT_TRUE( const_it.has_element() );

		EXPECT_EQ( it.peek(), i );
		EXPECT_EQ( it.fetch(), i );
		EXPECT_EQ( const_it.peek(), i );
		EXPECT_EQ( const_it.fetch(), i );
	}

	EXPECT_FALSE( it.has_element() );
	EXPECT_FALSE( const_it.has_element() );

	EXPECT_THROW( it.peek(), std::range_error );
	EXPECT_THROW( it.fetch(), std::range_error );
	EXPECT_THROW( const_it.peek(), std::range_error );
	EXPECT_THROW( const_it.fetch(), std::range_error );
}
