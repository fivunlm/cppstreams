//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_SKIP_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_SKIP_ITERATOR_H

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
			class skip_iterator : public transformation_iterator<T, T, Pointer> {
			protected:
				const size_t skip;
				size_t count;

			public:
				// DOCME
				skip_iterator( const Pointer<iterators::iterator<T> >& source, size_t skip );

				virtual const T fetch() override;
				virtual const T peek() override;
				virtual bool has_element() override;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			skip_iterator<T, Pointer>::skip_iterator( const Pointer<iterators::iterator<T> >& source, size_t skip ) :
				transformation_iterator<T, T, Pointer>( source ),
				skip( skip ),
				count( 0 ) {}

			template<class T, template<class> class Pointer>
			const T skip_iterator<T, Pointer>::fetch() {
				// Calls has_element(), which advances the iterator if necessary
				iterator<T>::check_state();

				return transformation_iterator<T, T, Pointer>::source->fetch();
			}

			template<class T, template<class> class Pointer>
			const T skip_iterator<T, Pointer>::peek() {
				// Calls has_element(), which advances the iterator if necessary
				iterator<T>::check_state();

				return transformation_iterator<T, T, Pointer>::source->peek();
			}

			template<class T, template<class> class Pointer>
			bool skip_iterator<T, Pointer>::has_element() {
				// Advancing logic
				while ( (++count <= skip) && transformation_iterator<T, T, Pointer>::source->has_element() ) {
					transformation_iterator<T, T, Pointer>::source->fetch();
				}

				return transformation_iterator<T, T, Pointer>::source->has_element();
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_SKIP_ITERATOR_H