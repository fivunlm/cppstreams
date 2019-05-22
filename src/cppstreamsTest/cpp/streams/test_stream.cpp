//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include <gtest/gtest.h>

#include <list>
#include <set>
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

TEST( Stream, AllMatch ) {
	EXPECT_FALSE( stream( values )->all_match( is_even ) );
	EXPECT_FALSE( stream( values )->all_match( is_odd ) );
	EXPECT_TRUE( stream( values )->filter( is_even )->all_match( is_even ) );
	EXPECT_FALSE( stream( values )->filter( is_even )->all_match( is_odd ) );
	EXPECT_FALSE( stream( values )->filter( is_odd )->all_match( is_even ) );
	EXPECT_TRUE( stream( values )->filter( is_odd )->all_match( is_odd ) );
}

TEST( Stream, AnyMatch ) {
	EXPECT_TRUE( stream( values )->any_match( is_even ) );
	EXPECT_TRUE( stream( values )->any_match( is_odd ) );
	EXPECT_TRUE( stream( values )->filter( is_even )->any_match( is_even ) );
	EXPECT_FALSE( stream( values )->filter( is_even )->any_match( is_odd ) );
	EXPECT_FALSE( stream( values )->filter( is_odd )->any_match( is_even ) );
	EXPECT_TRUE( stream( values )->filter( is_odd )->any_match( is_odd ) );
}

TEST( Stream, NoneMatch ) {
	EXPECT_FALSE( stream( values )->none_match( is_even ) );
	EXPECT_FALSE( stream( values )->none_match( is_odd ) );
	EXPECT_FALSE( stream( values )->filter( is_even )->none_match( is_even ) );
	EXPECT_TRUE( stream( values )->filter( is_even )->none_match( is_odd ) );
	EXPECT_TRUE( stream( values )->filter( is_odd )->none_match( is_even ) );
	EXPECT_FALSE( stream( values )->filter( is_odd )->none_match( is_odd ) );
}

TEST( Stream, Count ) {
	EXPECT_EQ( stream( values )->count(), 7 );
	EXPECT_EQ( stream( values )->filter( is_even )->count(), 3 );
	EXPECT_EQ( stream( values )->map<std::string>( to_string )->count(), 7 );
	EXPECT_EQ( stream( values )->filter( is_even )->map<std::string>( to_string )->count(), 3 );
}

TEST( Stream, Max ) {
	EXPECT_EQ( stream( values )->max(), 7 );

	EXPECT_EQ( stream( values )->filter( is_even )->max(), 6 );
	EXPECT_EQ( stream( values )->filter( is_odd )->max(), 7 );

	EXPECT_EQ( stream( values )->limit( 2 )->max(), 2 );
	EXPECT_EQ( stream( values )->skip( 2 )->max(), 7 );

	EXPECT_THROW( stream( values )->filter( is_even )->filter( is_odd )->max(), std::range_error );
	EXPECT_THROW( stream( values )->filter( is_odd )->filter( is_even )->max(), std::range_error );
}

TEST( Stream, MaxCustom ) {
	// With custom comparator
	EXPECT_EQ( stream( values )->max( std::greater<int>() ), 1 );

	EXPECT_EQ( stream( values )->filter( is_even )->max( std::greater<int>() ), 2 );
	EXPECT_EQ( stream( values )->filter( is_odd )->max( std::greater<int>() ), 1 );

	EXPECT_EQ( stream( values )->limit( 2 )->max( std::greater<int>() ), 1 );
	EXPECT_EQ( stream( values )->skip( 2 )->max( std::greater<int>() ), 3 );

	EXPECT_THROW( stream( values )->filter( is_even )->filter( is_odd )->max( std::greater<int>() ), std::range_error );
	EXPECT_THROW( stream( values )->filter( is_odd )->filter( is_even )->max( std::greater<int>() ), std::range_error );
}

TEST( Stream, Min ) {
	EXPECT_EQ( stream( values )->min(), 1 );

	EXPECT_EQ( stream( values )->filter( is_even )->min(), 2 );
	EXPECT_EQ( stream( values )->filter( is_odd )->min(), 1 );

	EXPECT_EQ( stream( values )->limit( 2 )->min(), 1 );
	EXPECT_EQ( stream( values )->skip( 2 )->min(), 3 );

	EXPECT_THROW( stream( values )->filter( is_even )->filter( is_odd )->min(), std::range_error );
	EXPECT_THROW( stream( values )->filter( is_odd )->filter( is_even )->min(), std::range_error );
}

TEST( Stream, MinCustom ) {
	// With custom comparator
	EXPECT_EQ( stream( values )->min( std::greater<int>() ), 7 );

	EXPECT_EQ( stream( values )->filter( is_even )->min( std::greater<int>() ), 6 );
	EXPECT_EQ( stream( values )->filter( is_odd )->min( std::greater<int>() ), 7 );

	EXPECT_EQ( stream( values )->limit( 2 )->min( std::greater<int>() ), 2 );
	EXPECT_EQ( stream( values )->skip( 2 )->min( std::greater<int>() ), 7 );

	EXPECT_THROW( stream( values )->filter( is_even )->filter( is_odd )->min( std::greater<int>() ), std::range_error );
	EXPECT_THROW( stream( values )->filter( is_odd )->filter( is_even )->min( std::greater<int>() ), std::range_error );
}

TEST( Stream, MultiFilter ) {
	EXPECT_EQ( stream( values )->filter( is_even )->filter( is_odd )->count(), 0 );
	EXPECT_EQ( stream( values )->filter( is_odd )->filter( is_even )->count(), 0 );

	EXPECT_EQ( stream( values )->filter( is_even )->filter( is_even )->count(), 3 );
	EXPECT_EQ( stream( values )->filter( is_odd )->filter( is_odd )->count(), 4 );
}

TEST( Stream, ReduceConst ) {
	EXPECT_EQ( stream( values )->reduce( (std::function<int( const int&, const int& )>) std::plus<int>(), 0 ), 28 );
	{int result = stream( values )->reduce<int>( (std::function<int( const int&, const int& )>) []( const int& val, const int& difference ) { return difference - val; }, 28 ); EXPECT_EQ( result, 0 ); }
	EXPECT_EQ( stream( values )->reduce( (std::function<int( const int&, const int& )>) std::multiplies<int>(), 1 ), 5040 );
	{ double result = stream( values )->reduce( (std::function<double( const int&, const double& )>) []( const int& val, const double& quotient ) { return quotient / val; }, 1.0 ); EXPECT_EQ( result, 1.0 / 5040.0 ); }
}

TEST( Stream, ReduceModify ) {
	{ int result = stream( values )->reduce<int>( []( const int& val, int& sum ) { sum += val; }, 0 ); EXPECT_EQ( result, 28 ); }
	{ int result = stream( values )->reduce<int>( []( const int& val, int& difference ) { difference -= val; }, 28 ); EXPECT_EQ( result, 0 ); }
	{ int result = stream( values )->reduce<int>( []( const int& val, int& product ) { product *= val; }, 1 ); EXPECT_EQ( result, 5040 ); }
	{ double result = stream( values )->reduce<double>( []( const int& val, double& quotient ) { quotient /= val; }, 1.0 ); EXPECT_EQ( result, 1.0 / 5040.0 ); }
}

TEST( Stream, Collect ) {
	EXPECT_EQ( stream( values )->collect( cppstreams::streams::to_list<int>() ), std::list<int>( std::begin( values ), std::end( values ) ) );
	EXPECT_EQ( stream( values )->collect( cppstreams::streams::to_set<int>() ), std::set<int>( std::begin( values ), std::end( values ) ) );
	EXPECT_EQ( stream( values )->collect( cppstreams::streams::to_vector<int>() ), std::vector<int>( std::begin( values ), std::end( values ) ) );
	EXPECT_EQ( stream( values )->collect(), std::vector<int>( std::begin( values ), std::end( values ) ) );
}
