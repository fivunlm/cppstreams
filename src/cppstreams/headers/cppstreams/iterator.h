//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATOR_H

// Namespace definitions and docs first
namespace cppstreams {
	/**
	* This namespace contains all iterator classes.
	*
	* This includes the base class <code>cppstreams::iterators::iterator<T></code> which will be aliased as
	* <code>cppstreams::iterator<T></code> as well as all sub clases.
	*/
	namespace iterators {
	}
}

// Includes
#include "cppstreams/iterators/iterator.h"

// Definitions and code
namespace cppstreams {
	// Aliasing

	/// @copydoc iterators::iterator
	template<class T>
	using iterator = iterators::iterator<T>;
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATOR_H
