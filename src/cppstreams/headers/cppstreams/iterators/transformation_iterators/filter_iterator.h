//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_FILTER_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_FILTER_ITERATOR_H

#include <functional>

#include "cppstreams/iterators/transformation_iterators/transformation_iterator.h"

namespace cppstreams {
	namespace iterators {
		namespace transformation_iterators {
			// DOCME
			template<class T, template<class> class Pointer = std::shared_ptr>
			class filter_iterator : public transformation_iterator<T, T, Pointer> {
			protected:
				const std::function<bool( const T& )> filter;

			public:
				// DOCME
				filter_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<bool( const T& )>& filter );

				virtual const T fetch() override;
				virtual const T peek() override;
				virtual bool has_element() override;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			filter_iterator<T, Pointer>::filter_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<bool( const T& )>& filter ) :
				transformation_iterator<T, T, Pointer>( source ),
				filter( filter ) {}

			template<class T, template<class> class Pointer>
			const T filter_iterator<T, Pointer>::fetch() {
				// Calls has_element(), which advances the iterator if necessary
				iterator<T>::check_state();

				return transformation_iterator<T, T, Pointer>::source->fetch();
			}

			template<class T, template<class> class Pointer>
			const T filter_iterator<T, Pointer>::peek() {
				// Calls has_element(), which advances the iterator if necessary
				iterator<T>::check_state();

				return transformation_iterator<T, T, Pointer>::source->peek();
			}

			template<class T, template<class> class Pointer>
			bool filter_iterator<T, Pointer>::has_element() {
				// Advancing logic
				while ( transformation_iterator<T, T, Pointer>::source->has_element() && !filter( transformation_iterator<T, T, Pointer>::source->peek() ) ) {
					transformation_iterator<T, T, Pointer>::source->fetch();
				}

				return transformation_iterator<T, T, Pointer>::source->has_element();
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_FILTER_ITERATOR_H