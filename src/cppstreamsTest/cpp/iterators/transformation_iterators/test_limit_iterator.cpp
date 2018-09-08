//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "utilities.h"

#include "cppstreams/iterator.h"

using cppstreams::iterators::transformation_iterators::limit_iterator;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Iterator_TransformationInterator_LimitIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( values ) );

	EXPECT_NO_THROW( limit_iterator<int> limit_it( it, 10 ) );

	EXPECT_NO_THROW( limit_iterator<int> limit_it( const_it, 10 ) );
}

TEST( Iterator_TransformationInterator_LimitIterator, Iterating ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	limit_iterator<int> limit_it( it, 5 );

	for ( int i = 1; i <= 5; ++i ) {
		EXPECT_TRUE( limit_it.has_element() );

		EXPECT_EQ( limit_it.peek(), i );
		EXPECT_EQ( limit_it.fetch(), i );
	}

	EXPECT_FALSE( limit_it.has_element() );

	EXPECT_THROW( limit_it.peek(), std::range_error );
	EXPECT_THROW( limit_it.fetch(), std::range_error );
}
