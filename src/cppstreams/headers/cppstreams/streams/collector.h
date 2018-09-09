//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTOR_H

// Namespace definitions and docs first
namespace cppstreams {
	namespace streams {
		// DOCME
		namespace collectors {
		}
	}
}

// Includes
#include <functional>
#include <list>
#include <set>
#include <vector>

#include "cppstreams/streams/collectors/collector.h"
#include "cppstreams/streams/collectors/insert_collector.h"
#include "cppstreams/streams/collectors/push_back_collector.h"

// Definitions and code
namespace cppstreams {
	namespace streams {
		// TODO: Split deklaration and implementation
		// Convinience Methods

		// Geneic collectors

		// DOCME
		// TESTME
		template<class T, class Container, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, Container > > collector( std::function<Container()> instance_provider, std::function<void( const T&, Container& )> accumulator_function ) {
			static const Pointer<collectors::collector<T, Container> > collector(
				Pointer<collectors::collector<T, Container> >(
					new collectors::collector<T, Container>( instance_provider, accumulator_function )
				)
			);

			return collector;
		}

		// DOCME
		template<class T, class Container, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, Container > > insert_collector() {
			static const Pointer<collectors::collector<T, Container> > collector(
				Pointer<collectors::collector<T, Container> >( new collectors::insert_collector<T, Container>() )
			);

			return collector;
		}

		// DOCME
		template<class T, class Container, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, Container > > push_back_collector() {
			static const Pointer<collectors::collector<T, Container> > collector(
				Pointer<collectors::collector<T, Container> >( new collectors::push_back_collector<T, Container>() )
			);

			return collector;
		}

		// TODO: Add methods for all STL containers
		// TODO: Allow passing of additional template parameters
		// STL collectors

		// DOCME
		template<class T, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::list<T> > > to_list() {
			return push_back_collector<T, std::list<T>, Pointer>();
		}

		// DOCME
		template<class T, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::set<T> > > to_set() {
			return insert_collector<T, std::set<T>, Pointer>();
		}

		// DOCME
		template<class T, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::vector<T> > > to_vector() {
			return push_back_collector<T, std::vector<T>, Pointer>();
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTOR_H
