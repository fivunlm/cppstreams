//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_TRANSFORMATION_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_TRANSFORMATION_ITERATOR_H

#include <memory>

#include "cppstreams/iterators/iterator.h"

namespace cppstreams {
	namespace iterators {
		namespace transformation_iterators {
			// DOCME
			template<class T, template<class> class Pointer = std::shared_ptr>
			class transformation_iterator : public iterator<T> {
			protected:
				// DOCME
				const Pointer<iterators::iterator<T> > source;

				// DOCME
				transformation_iterator( const Pointer<iterators::iterator<T> >& source );
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			transformation_iterator<T, Pointer>::transformation_iterator( const Pointer<iterators::iterator<T> >& source ) :
				source( source ) {}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_TRANSFORMATION_ITERATOR_H