//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_CONTAINER_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_CONTAINER_ITERATOR_H

#include <iterator>

#include "cppstreams/iterators/iterator.h"

namespace cppstreams {
	namespace iterators {
		// DOCME
		template<class Container, class T = std::decay_t<decltype(*std::begin( Container() ))>>
		class container_iterator : public iterator<T> {
		public:
			// DOCME
			typedef decltype(std::begin( Container() )) iterator_type;

		protected:
			// DOCME
			iterator_type it;
			// DOCME
			const iterator_type end;

		public:
			// DOCME
			container_iterator( const iterator_type& start, const iterator_type& end );
			// DOCME
			container_iterator( const Container& container );

			virtual const T next();

			virtual bool hasNext() const noexcept;
		};

		template<class Container, class T>
		container_iterator<Container, T>::container_iterator( const iterator_type& start, const iterator_type& end ) :
			it( start ),
			end( end ) {}

		template<class Container, class T>
		container_iterator<Container, T>::container_iterator( const Container& container ) :
			container_iterator( std::begin( container ), std::end( container ) ) {}

		template<class Container, class T>
		const T container_iterator<Container, T>::next() {
			return *(it++);
		}

		template<class Container, class T>
		bool container_iterator<Container, T>::hasNext() const noexcept {
			return it != end;
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_CONTAINER_ITERATOR_H