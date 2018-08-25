//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H

// Includes
#include <memory>

#include "cppstreams/iterator.h"

namespace cppstreams {
	namespace streams {
		/**
		 * Base stream class.
		 *
		 * This class already is a functional stream. Though it can be extended to allow streams with different
		 * behaviors.
		 */
		template<class T, template<class> class Pointer = std::shared_ptr>
		class stream {
		protected:
			const Pointer<iterators::iterator<T> > source;

		public:
			stream( const Pointer<iterators::iterator<T> >& source );
		};

		// ==============================================================================
		// Implementation
		// ==============================================================================

		template<class T, template<class> class Pointer>
		stream<T, Pointer>::stream( const Pointer<iterators::iterator<T> >& source ) :
			source( source ) {}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
