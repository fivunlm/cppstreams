//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_PUSH_BACK_COLLECTOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_PUSH_BACK_COLLECTOR_H

#include "cppstreams/streams/collectors/collector.h"

namespace cppstreams {
	namespace streams {
		namespace collectors {
			// DOCME
			template<class T, class Container>
			class push_back_collector : public collector<T, Container> {
			public:
				push_back_collector();
			};

			// ==============================================================================
			// Implementation
			// ==============================================================================

			template<class T, class Container>
			push_back_collector<T, Container>::push_back_collector() :
				collector<T, Container>::collector(
					[]() { return Container(); },
					[]( const T& val, Container& container ) { container.push_back( val ); }
				) {}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTORS_PUSH_BACK_COLLECTOR_H
