//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_COLLECTOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_COLLECTOR_H

#include <functional>

namespace cppstreams {
	namespace streams {
		namespace collectors {
			// DOCME
			template<class T, class Container>
			class collector {
			public:
				// DOCME
				typedef T value_type;
				// DOCME
				typedef Container container_type;

			protected:
				const std::function<Container()> instance_provider;
				const std::function<void( const T&, Container& )> accumulator_function;

			public:
				// DOCME
				collector( std::function<Container()> instance_provider, std::function<void( const T&, Container& )> accumulator_function );

				// DOCME
				virtual Container create_instance() const;
				// DOCME
				virtual std::function<void( const T&, Container& )> accumulator() const;
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, class Container>
			collector<T, Container>::collector( std::function<Container()> instance_provider, std::function<void( const T&, Container& )> accumulator_function ) :
				instance_provider( instance_provider ),
				accumulator_function( accumulator_function ) {}

			template<class T, class Container>
			Container collector<T, Container>::create_instance() const {
				return instance_provider();
			}

			template<class T, class Container>
			std::function<void( const T&, Container& )> collector<T, Container>::accumulator() const {
				return accumulator_function;
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_COLLECTOR_H