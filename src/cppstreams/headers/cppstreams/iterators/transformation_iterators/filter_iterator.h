//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
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
			class filter_iterator : public transformation_iterator<T, Pointer> {
			protected:
				const std::function<bool( const T& )> filter;

			public:
				// DOCME
				filter_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<bool( const T& )>& filter );

				virtual const T next();
				virtual const T peek();
				virtual bool has_next();

			protected:
				void advance();
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, template<class> class Pointer>
			filter_iterator<T, Pointer>::filter_iterator( const Pointer<iterators::iterator<T> >& source, const std::function<bool( const T& )>& filter ) :
				transformation_iterator( source ),
				filter( filter ) {}

			template<class T, template<class> class Pointer>
			const T filter_iterator<T, Pointer>::next() {
				advance();

				return source->next();
			}

			template<class T, template<class> class Pointer>
			const T filter_iterator<T, Pointer>::peek() {
				advance();

				return source->peek();
			}

			template<class T, template<class> class Pointer>
			bool filter_iterator<T, Pointer>::has_next() {
				advance();

				return source->has_next();
			}

			template<class T, template<class> class Pointer>
			void filter_iterator<T, Pointer>::advance() {
				while ( source->has_next() && !filter( source->peek() ) ) {
					source->next();
				}
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_FILTER_ITERATOR_H