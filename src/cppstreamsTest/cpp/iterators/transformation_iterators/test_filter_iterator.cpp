//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include "cppstreams/iterator.h"

template<class T>
using filter_iterator = cppstreams::iterators::transformation_iterators::filter_iterator<T>;

bool is_even( const int& num ) {
	return (num % 2) == 0;
}

TEST( Iterator_TransformationInterator_FilterIterator, Constructors ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( { 1, 2, 3, 4, 5, 6 } ) );
	const std::shared_ptr<cppstreams::iterators::iterator<int> > const_it( cppstreams::get_iterator( { 1, 2, 3, 4, 5, 6 } ) );

	EXPECT_NO_THROW( filter_iterator<int> filter_it( it, is_even ) );

	EXPECT_NO_THROW( filter_iterator<int> filter_it( const_it, is_even ) );
}

TEST( Iterator_TransformationInterator_FilterIterator, Iterating ) {
	std::shared_ptr<cppstreams::iterators::iterator<int> > it( cppstreams::get_iterator( { 1, 2, 3, 4, 5, 6 } ) );
	filter_iterator<int> filter_it( it, is_even );

	for ( int i = 2; i <= 6; i += 2 ) {
		EXPECT_TRUE( filter_it.has_next() );

		EXPECT_EQ( filter_it.peek(), i );
		EXPECT_EQ( filter_it.next(), i );
	}

	EXPECT_FALSE( filter_it.has_next() );
}
