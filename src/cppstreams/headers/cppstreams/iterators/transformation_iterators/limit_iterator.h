//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_LIMIT_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_LIMIT_ITERATOR_H

// Include version check
#include "cppstreams/version_check.h"

// Includes
#include <functional>

#include "cppstreams/iterators/transformation_iterators/transformation_iterator.h"

namespace cppstreams {
	namespace iterators {
		namespace transformation_iterators {
			// DOCME
			template<class T, template<class> class Pointer = std::shared_ptr>
			class limit_iterator : public transformation_iterator<T, T, Pointer> {
			protected:
				const size_t limit;
				size_t count;

			public:
				// DOCME
				limit_iterator( const Pointer<iterators::iterator<T> >& source, size_t limit );

				virtual const T fetch() override;
				virtual const T peek() override;
				virtual bool has_element() override;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			limit_iterator<T, Pointer>::limit_iterator( const Pointer<iterators::iterator<T> >& source, size_t limit ) :
				transformation_iterator<T, T, Pointer>( source ),
				limit( limit ),
				count( 0 ) {}

			template<class T, template<class> class Pointer>
			const T limit_iterator<T, Pointer>::fetch() {
				iterator<T>::check_state();

				++count;

				return transformation_iterator<T, T, Pointer>::source->fetch();
			}

			template<class T, template<class> class Pointer>
			const T limit_iterator<T, Pointer>::peek() {
				iterator<T>::check_state();

				return transformation_iterator<T, T, Pointer>::source->peek();
			}

			template<class T, template<class> class Pointer>
			bool limit_iterator<T, Pointer>::has_element() {
				if ( count >= limit )
					return false;

				return transformation_iterator<T, T, Pointer>::source->has_element();
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_LIMIT_ITERATOR_H