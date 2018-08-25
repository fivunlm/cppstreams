//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAM_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAM_H

// Namespace definitions and docs first
namespace cppstreams {
	/**
	 * This namespace contains all stream classes.
	 *
	 * This includes the base class <code>cppstreams::streams::stream<T></code> which will be aliased as
	 * <code>cppstreams::stream<T></code> as well as all sub clases.
	 */
	namespace streams {
	}
}

// Includes
#include <memory>

#include "cppstreams/streams/stream.h"
#include "cppstreams/iterator.h"

// Definitions and code
namespace cppstreams {
	// Convinience Methods

	// DOCME
	// TESTME
	template<class T, template<class> class Pointer = std::shared_ptr>
	Pointer<streams::stream<T, Pointer> > stream(
		const Pointer<iterators::iterator<T> >& iterator
	);

	// DOCME
	// TESTME
	// TODO: Get template deduction working
	template<class T, template<class> class Pointer = std::shared_ptr>
	Pointer<streams::stream<T, Pointer> > stream(
		const typename iterators::array_iterator<T>::iterator_type start,
		const typename iterators::array_iterator<T>::iterator_type end
	);

	// DOCME
	// TESTME
	template<class T, std::size_t N, template<class> class Pointer = std::shared_ptr>
	Pointer<streams::stream<T, Pointer> > stream(
		const T( &array )[N]
	);

	// DOCME
	// TESTME
	// TODO: Get template deduction working
	template<class Container, class T = typename std::decay<decltype(*std::begin( Container() ))>::type, template<class> class Pointer = std::shared_ptr>
	Pointer<streams::stream<T, Pointer> > stream(
		const typename iterators::container_iterator<Container, T>::iterator_type start,
		const typename iterators::container_iterator<Container, T>::iterator_type end
	);

	// DOCME
	// TESTME
	template<class Container, class T = typename std::decay<decltype(*std::begin( Container() ))>::type, template<class> class Pointer = std::shared_ptr>
	Pointer<streams::stream<T, Pointer> > stream(
		const Container& container
	);

	// ==============================================================================
	// Implementation
	// ==============================================================================

	template<class T, template<class> class Pointer>
	Pointer<streams::stream<T, Pointer> > stream(
		const Pointer<iterators::iterator<T> >& iterator
	) {
		return Pointer<streams::stream<T, Pointer> >( new streams::stream<T, Pointer>( iterator ) );
	}

	template<class T, template<class> class Pointer>
	Pointer<streams::stream<T, Pointer> > stream(
		const typename iterators::array_iterator<T>::iterator_type start,
		const typename iterators::array_iterator<T>::iterator_type end
	) {
		return Pointer<streams::stream<T, Pointer> >( new streams::stream<T, Pointer>( get_iterator<T, Pointer>( start, end ) ) );
	}

	template<class T, std::size_t N, template<class> class Pointer>
	Pointer<streams::stream<T, Pointer> > stream(
		const T( &array )[N]
	) {
		return Pointer<streams::stream<T, Pointer> >( new streams::stream<T, Pointer>( get_iterator<T, N, Pointer>( array ) ) );
	}

	template<class Container, class T, template<class> class Pointer>
	Pointer<streams::stream<T, Pointer> > stream(
		const typename iterators::container_iterator<Container, T>::iterator_type start,
		const typename iterators::container_iterator<Container, T>::iterator_type end
	) {
		return Pointer<streams::stream<T, Pointer> >( new streams::stream<T, Pointer>( get_iterator<Container, T, Pointer>( start, end ) ) );
	}

	template<class Container, class T, template<class> class Pointer>
	Pointer<streams::stream<T, Pointer> > stream(
		const Container& container
	) {
		return Pointer<streams::stream<T, Pointer> >( new streams::stream<T, Pointer>( get_iterator<Container, T, Pointer>( container ) ) );
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAM_H
