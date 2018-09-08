//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "utilities.h"

#include "cppstreams/iterator.h"

using cppstreams::iterators::transformation_iterators::peek_iterator;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Iterator_TransformationInterator_PeekIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( values ) );

	// Even works with functions returning something
	EXPECT_NO_THROW( peek_iterator<int> peek_it( it, is_even ) );

	EXPECT_NO_THROW( peek_iterator<int> peek_it( const_it, is_even ) );
}

TEST( Iterator_TransformationInterator_PeekIterator, Iterating ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	int sum = 0;
	peek_iterator<int> peek_it( it, [&sum]( const int& val ) { sum += val; } );

	for ( int i = 1; i <= 7; ++i ) {
		EXPECT_TRUE( peek_it.has_element() );

		EXPECT_EQ( peek_it.peek(), i );
		EXPECT_EQ( peek_it.fetch(), i );
	}

	EXPECT_FALSE( peek_it.has_element() );

	EXPECT_THROW( peek_it.peek(), std::range_error );
	EXPECT_THROW( peek_it.fetch(), std::range_error );

	EXPECT_EQ( sum, 28 );
}
