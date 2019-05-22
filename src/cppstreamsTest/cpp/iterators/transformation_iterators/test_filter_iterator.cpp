//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "utilities.h"

#include "cppstreams/iterator.h"

using cppstreams::iterators::transformation_iterators::filter_iterator;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Iterator_TransformationInterator_FilterIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( values ) );

	EXPECT_NO_THROW( filter_iterator<int> filter_it( it, is_even ) );

	EXPECT_NO_THROW( filter_iterator<int> filter_it( const_it, is_even ) );
}

TEST( Iterator_TransformationInterator_FilterIterator, Iterating ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( values ) );
	filter_iterator<int> filter_it( it, is_even );

	for ( int i = 2; i <= 6; i += 2 ) {
		EXPECT_TRUE( filter_it.has_element() );

		EXPECT_EQ( filter_it.peek(), i );
		EXPECT_EQ( filter_it.fetch(), i );
	}

	EXPECT_FALSE( filter_it.has_element() );

	EXPECT_THROW( filter_it.peek(), std::range_error );
	EXPECT_THROW( filter_it.fetch(), std::range_error );
}
