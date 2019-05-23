//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
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

#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <vector>

#include <map>

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
		// STL container collectors

		// DOCME
		// TESTME
		template<class T, class Allocator = typename std::deque<T>::allocator_type, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::deque<T, Allocator> > > to_deque() {
			return push_back_collector<T, std::deque<T, Allocator>, Pointer>();
		}

		// DOCME
		// TESTME
		template<class T, class Allocator = typename std::forward_list<T>::allocator_type, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::forward_list<T, Allocator> > > to_forward_list() {
			return push_back_collector<T, std::forward_list<T, Allocator>, Pointer>();
		}

		// DOCME
		template<class T, class Allocator = typename std::list<T>::allocator_type, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::list<T, Allocator> > > to_list() {
			return push_back_collector<T, std::list<T, Allocator>, Pointer>();
		}

		// DOCME
		template<class T, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::set<T> > > to_set() {
			return insert_collector<T, std::set<T>, Pointer>();
		}

		// DOCME
		template<class T, class Allocator = typename std::vector<T>::allocator_type, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<T, std::vector<T, Allocator> > > to_vector() {
			return push_back_collector<T, std::vector<T, Allocator>, Pointer>();
		}

		// STL map container collectors

		// DOCME
		// TESTME
		template<class Key, class T, class Comparator = std::less<Key>, class Allocator = typename std::allocator<std::pair<const Key, T> >, template<class> class Pointer = std::shared_ptr>
		Pointer<collectors::collector<std::pair<const Key, T>, std::map<Key, T, Comparator, Allocator> > > to_map() {
			return insert_collector<std::pair<const Key, T>, std::map<Key, T, Comparator, Allocator>, Pointer>();
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_COLLECTOR_H
