//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "cppstreams/iterators/array_iterator.h"

template<class T>
using array_iterator = cppstreams::iterators::array_iterator<T>;

int array[] = { 1, 2, 3 };
constexpr int const_array[] = { 1, 2, 3 };

TEST( Iterator_ArrayIterator, Constructors ) {
	EXPECT_NO_THROW( array_iterator<int> it( array ) );
	EXPECT_NO_THROW( array_iterator<int> it( array, array + 3 ) );

	EXPECT_NO_THROW( array_iterator<int> it( const_array ) );
	EXPECT_NO_THROW( array_iterator<int> it( const_array, const_array + 3 ) );
}

TEST( Iterator_ArrayIterator, Iterating ) {
	array_iterator<int> it( array );
	array_iterator<int> const_it( const_array );

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
