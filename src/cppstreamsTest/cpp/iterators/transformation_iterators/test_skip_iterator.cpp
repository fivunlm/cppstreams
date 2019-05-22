//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "utilities.h"

#include "cppstreams/iterator.h"

using cppstreams::iterators::transformation_iterators::skip_iterator;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Iterator_TransformationInterator_SkipIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( values ) );

	EXPECT_NO_THROW( skip_iterator<int> skip_it( it, 10 ) );

	EXPECT_NO_THROW( skip_iterator<int> skip_it( const_it, 10 ) );
}

TEST( Iterator_TransformationInterator_SkipIterator, Iterating ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	skip_iterator<int> skip_it( it, 4 );

	for ( int i = 5; i <= 7; ++i ) {
		EXPECT_TRUE( skip_it.has_element() );

		EXPECT_EQ( skip_it.peek(), i );
		EXPECT_EQ( skip_it.fetch(), i );
	}

	EXPECT_FALSE( skip_it.has_element() );

	EXPECT_THROW( skip_it.peek(), std::range_error );
	EXPECT_THROW( skip_it.fetch(), std::range_error );
}
