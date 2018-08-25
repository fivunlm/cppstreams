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
#include <memory>

#include "cppstreams/iterators/iterator.h"
#include "cppstreams/iterators/array_iterator.h"
#include "cppstreams/iterators/container_iterator.h"

// Definitions and code
namespace cppstreams {
	// Convinience Methods

	// DOCME
	template<class T, template<class> class Pointer = std::shared_ptr>
	Pointer<iterators::iterator<T> > get_iterator(
		const typename iterators::array_iterator<T>::iterator_type start,
		const typename iterators::array_iterator<T>::iterator_type end
	);

	// DOCME
	template<class T, std::size_t N, template<class> class Pointer = std::shared_ptr>
	Pointer<iterators::iterator<T> > get_iterator(
		const T( &array )[N]
	);

	// DOCME
	template<class Container, class T = typename std::decay<decltype(*std::begin( Container() ))>::type, template<class> class Pointer = std::shared_ptr>
	Pointer<iterators::iterator<T> > get_iterator(
		const typename iterators::container_iterator<Container, T>::iterator_type start,
		const typename iterators::container_iterator<Container, T>::iterator_type end
	);

	// DOCME
	template<class Container, class T = typename std::decay<decltype(*std::begin( Container() ))>::type, template<class> class Pointer = std::shared_ptr>
	Pointer<iterators::iterator<T> > get_iterator(
		const Container& container
	);

	// ==============================================================================
	// Implementation
	// ==============================================================================

	template<class T, template<class> class Pointer>
	Pointer<iterators::iterator<T> > get_iterator(
		const typename iterators::array_iterator<T>::iterator_type start,
		const typename iterators::array_iterator<T>::iterator_type end
	) {
		return Pointer<iterators::iterator<T> >( new iterators::array_iterator<T>( start, end ) );
	}

	template<class T, std::size_t N, template<class> class Pointer = std::shared_ptr>
	Pointer<iterators::iterator<T> > get_iterator(
		const T( &array )[N]
	) {
		return Pointer<iterators::iterator<T> >( new iterators::array_iterator<T>( array ) );
	}

	template<class Container, class T, template<class> class Pointer>
	Pointer<iterators::iterator<T> > get_iterator(
		const typename iterators::container_iterator<Container, T>::iterator_type start,
		const typename iterators::container_iterator<Container, T>::iterator_type end
	) {
		return Pointer<iterators::iterator<T> >( new iterators::container_iterator<Container, T>( start, end ) );
	}

	template<class Container, class T, template<class> class Pointer>
	Pointer<iterators::iterator<T> > get_iterator(
		const Container& container
	) {
		return Pointer<iterators::iterator<T> >( new iterators::container_iterator<Container, T>( container ) );
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATOR_H
