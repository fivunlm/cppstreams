//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H

// Includes
#include <functional>
#include <memory>

#include "cppstreams/iterator.h"

namespace cppstreams {
	namespace streams {
		/**
		 * Base stream class.
		 *
		 * This class already is a functional stream. Though it can be extended to allow streams with different
		 * behaviors.
		 *
		 * @tparam T The value type (see <code>stream::value_type</code>)
		 * @tparam Pointer This template parameter determines which smart pointer to use.<br>
		 *                 To prevent memory leaks, this library only uses smart pointers.<br>
		 *                 Default is <code>std::shared_ptr</code>
		 */
		template<class T, template<class> class Pointer = std::shared_ptr>
		class stream {
		public:
			// DOCME
			typedef T value_type;

		protected:
			// DOCME
			const Pointer<iterators::iterator<T> > source;

		public:
			// DOCME
			stream( const Pointer<iterators::iterator<T> >& source );

			// DOCME
			// TESTME
			Pointer<stream<T, Pointer> > filter( std::function<bool( const T& )> filter );
		};

		// ==============================================================================
		// Implementation
		// ==============================================================================

		template<class T, template<class> class Pointer>
		stream<T, Pointer>::stream( const Pointer<iterators::iterator<T> >& source ) :
			source( source ) {}

		template<class T, template<class> class Pointer>
		Pointer<stream<T, Pointer> > stream<T, Pointer>::filter( std::function<bool( const T& )> filter ) {
			return Pointer<stream<T, Pointer> >( new stream<T, Pointer>( iterators::transformation_iterators::filter_iterator<T, Pointer>( source, filter ) ) );
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
