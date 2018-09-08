//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_PEEK_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_PEEK_ITERATOR_H

#include <functional>

#include "cppstreams/iterators/transformation_iterators/transformation_iterator.h"

namespace cppstreams {
	namespace iterators {
		namespace transformation_iterators {
			// DOCME
			template<class T, template<class> class Pointer = std::shared_ptr>
			class peek_iterator : public transformation_iterator<T, T, Pointer> {
			protected:
				const std::function<void( const T& )> peeker;

			public:
				// DOCME
				peek_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<void( const T& )>& peeker );

				virtual const T fetch() override;
				virtual const T peek() override;
				virtual bool has_element() override;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			peek_iterator<T, Pointer>::peek_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<void( const T& )>& peeker ) :
				transformation_iterator<T, T, Pointer>( source ),
				peeker( peeker ) {}

			template<class T, template<class> class Pointer>
			const T peek_iterator<T, Pointer>::fetch() {
				// Prevent copying as much as possible by not storing the output of <code>fetch()</code> in a variable
				peeker( transformation_iterator<T, T, Pointer>::source->peek() );

				return transformation_iterator<T, T, Pointer>::source->fetch();
			}

			template<class T, template<class> class Pointer>
			const T peek_iterator<T, Pointer>::peek() {
				return transformation_iterator<T, T, Pointer>::source->peek();
			}

			template<class T, template<class> class Pointer>
			bool peek_iterator<T, Pointer>::has_element() {
				return transformation_iterator<T, T, Pointer>::source->has_element();
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_PEEK_ITERATOR_H