//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H

namespace cppstreams {
	namespace iterators {
		/**
		 * Abstract iterator class designed to provide a generic interface for all kinds of containers.
		 *
		 * To support more containers, we just need to add more subclasses.
		 */
		template<class T>
		class iterator {};
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H