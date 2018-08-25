//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ARRAY_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ARRAY_ITERATOR_H

#include <iterator>

#include "cppstreams/iterators/iterator.h"

namespace cppstreams {
	namespace iterators {
		// DOCME
		template<class T>
		class array_iterator : public iterator<T> {
		public:
			// DOCME
			typedef const T* iterator_type;

		protected:
			// DOCME
			iterator_type it;
			// DOCME
			const iterator_type end;

		public:
			// DOCME
			array_iterator( const iterator_type start, const iterator_type end );
			// DOCME
			template<std::size_t N>
			array_iterator( const T( &array )[N] );

			virtual const T next();
			virtual const T peek();
			virtual bool has_next();
		};

		// ==============================================================================
		// Implementation
		// ==============================================================================

		template<class T>
		array_iterator<T>::array_iterator( const iterator_type start, const iterator_type end ) :
			it( start ),
			end( end ) {}

		template<class T>
		template<std::size_t N>
		array_iterator<T>::array_iterator( const T( &array )[N] ) :
			array_iterator( std::begin( array ), std::end( array ) ) {}

		template<class T>
		const T array_iterator<T>::next() {
			return *(it++);
		}

		template<class T>
		const T array_iterator<T>::peek() {
			return *it;
		}

		template<class T>
		bool array_iterator<T>::has_next() {
			return it != end;
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ARRAY_ITERATOR_H
