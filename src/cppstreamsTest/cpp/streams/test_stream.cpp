//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include <string>

#include "utilities.h"

#include "cppstreams/stream.h"

using cppstreams::stream;

constexpr int values[] { 1, 2, 3, 4, 5, 6, 7 };

TEST( Stream, Lambda ) {
	size_t count;

	// Need to do it that way. Lambdas don't work inside EXPECT_EQ
	count = stream( values )->count(); EXPECT_EQ( count, 7 );
	count = stream( values )->filter( []( const int& val ) { return (val % 2) == 0; } )->count(); EXPECT_EQ( count, 3 );
	count = stream( values )->map<std::string>( []( const int& val ) { return std::to_string( val ); } )->count(); EXPECT_EQ( count, 7 );
	count = stream( values )->filter( []( const int& val ) { return (val % 2) == 0; } )->map<std::string>( []( const int& val ) { return std::to_string( val ); } )->count(); EXPECT_EQ( count, 3 );
}

TEST( Stream, Count ) {
	EXPECT_EQ( stream( values )->count(), 7 );
	EXPECT_EQ( stream( values )->filter( is_even )->count(), 3 );
	EXPECT_EQ( stream( values )->map<std::string>( to_string )->count(), 7 );
	EXPECT_EQ( stream( values )->filter( is_even )->map<std::string>( to_string )->count(), 3 );
}

TEST( Stream, MultiFilter ) {
	EXPECT_EQ( stream( values )->filter( is_even )->filter( is_odd )->count(), 0 );
	EXPECT_EQ( stream( values )->filter( is_odd )->filter( is_even )->count(), 0 );

	EXPECT_EQ( stream( values )->filter( is_even )->filter( is_even )->count(), 3 );
	EXPECT_EQ( stream( values )->filter( is_odd )->filter( is_odd )->count(), 4 );
}
