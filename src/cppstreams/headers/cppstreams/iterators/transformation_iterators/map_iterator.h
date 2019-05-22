//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_MAP_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_MAP_ITERATOR_H

#include <functional>

#include "cppstreams/iterators/transformation_iterators/transformation_iterator.h"

namespace cppstreams {
	namespace iterators {
		namespace transformation_iterators {
			// DOCME
			template<class In, class Out, template<class> class Pointer = std::shared_ptr>
			class map_iterator : public transformation_iterator<In, Out, Pointer> {
			protected:
				const std::function<Out( const In& )> mapper;

			public:
				// DOCME
				map_iterator( const Pointer<iterators::iterator<In> >& source, const std::function<Out( const In& )>& mapper );

				virtual const Out fetch() override;
				virtual const Out peek() override;
				virtual bool has_element() override;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class In, class Out, template<class> class Pointer>
			map_iterator<In, Out, Pointer>::map_iterator( const Pointer<iterators::iterator<In> >& source, const std::function<Out( const In& )>& mapper ) :
				transformation_iterator<In, Out, Pointer>( source ),
				mapper( mapper ) {}

			template<class In, class Out, template<class> class Pointer>
			const Out map_iterator<In, Out, Pointer>::fetch() {
				// Call to source->fetch() already calls check_state()
				return mapper( transformation_iterator<In, Out, Pointer>::source->fetch() );
			}

			template<class In, class Out, template<class> class Pointer>
			const Out map_iterator<In, Out, Pointer>::peek() {
				// Call to source->peek() already calls check_state()
				return mapper( transformation_iterator<In, Out, Pointer>::source->peek() );
			}

			template<class In, class Out, template<class> class Pointer>
			bool map_iterator<In, Out, Pointer>::has_element() {
				return transformation_iterator<In, Out, Pointer>::source->has_element();
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_TRANSFORMATION_ITERATORS_MAP_ITERATOR_H