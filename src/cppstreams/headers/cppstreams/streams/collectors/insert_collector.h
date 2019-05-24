//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_INSERT_COLLECTOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_INSERT_COLLECTOR_H

// Include version check
#include "cppstreams/version_check.h"

// Includes
#include "cppstreams/streams/collectors/collector.h"

namespace cppstreams {
	namespace streams {
		namespace collectors {
			// DOCME
			template<class T, class Container>
			class insert_collector : public collector<T, Container> {
			public:
				insert_collector();
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, class Container>
			insert_collector<T, Container>::insert_collector() :
				collector<T, Container>::collector(
					[]() { return Container(); },
					[]( const T& val, Container& container ) { container.insert( val ); }
				) {}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_INSERT_COLLECTOR_H
