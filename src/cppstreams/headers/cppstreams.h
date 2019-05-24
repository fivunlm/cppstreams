//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_H

// Check compiler compatibility and which C++ version is being used

/// Check for C++17 support
#ifndef CPPSTREAMS_CPP17
#	if (__cplusplus >= 201703L) || \
	(defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L))
/// C++17 available
#		define CPPSTREAMS_CPP17 1
#	else
/// C++17 not available
#		define CPPSTREAMS_CPP17 0
#	endif
#endif

/// Check for C++14 support
#ifndef CPPSTREAMS_CPP14
#	if CPPSTREAMS_CPP17 || \
	(__cplusplus >= 201402L) || \
    (defined(_MSVC_LANG) && (_MSVC_LANG >= 201402L))
/// C++14 available
#		define CPPSTREAMS_CPP14 1
#	else
/// C++14 not available
#		define CPPSTREAMS_CPP14 0
#	endif
#endif

/// Check for C++11 support
#ifndef CPPSTREAMS_CPP11
#	if CPPSTREAMS_CPP14 || \
	(__cplusplus >= 201103L) || \
	(defined(_MSC_VER) && (_MSC_VER >= 1700))
/// C++11 available
#		define CPPSTREAMS_CPP11 1
#	else
/// C++11 not available
#		define CPPSTREAMS_CPP11 0
#	endif
#endif

// We need at least C++11 support
#if ! CPPSTREAMS_CPP11
#	error The library cppstreams requires at least C++11! \
If this compiler supports C++11, but we failed to detect so, place "#define CPPSTREAMS_CPP11 1" before the include "#include <cppstreams.h>"
#endif

// Define the namespace (and provide docs)

/**
 * Main Namespace for the cppstreams lib.
 *
 * Everything of the library will exist inside this namespace.
 */
namespace cppstreams {
}

// Now the other includes
#include "cppstreams/stream.h"
#include "cppstreams/iterator.h"

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_H
