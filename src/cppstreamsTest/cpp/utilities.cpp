//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#include "utilities.h"

bool is_even( const int& val ) {
	return (val % 2) == 0;
}

bool is_odd( const int& val ) {
	return !is_even( val );
}

int negator( const int& val ) {
	return -val;
}

std::string to_string( const int& val ) {
	return std::to_string( val );
}

