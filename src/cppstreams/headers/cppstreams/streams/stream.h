//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H

// Include version check
#include "cppstreams/version_check.h"

// Includes
#include <functional>
#include <memory>
#if CPPSTREAMS_CPP17
#include <optional>
#endif

#include "cppstreams/iterator.h"
#include "cppstreams/streams/collector.h"

namespace cppstreams {
	namespace streams {
		/**
		 * Base stream class.
		 *
		 * This class already is a functional stream. Though it can be extended to allow streams with different
		 * behaviors.
		 *
		 * @tparam T The value type (see <code>stream::value_type</code>)
		 * @tparam Pointer This template parameter determines which smart pointer to use.<br>
		 *                 To prevent memory leaks, this library only uses smart pointers.<br>
		 *                 Default is <code>std::shared_ptr</code>
		 */
		template<class T, template<class> class Pointer = std::shared_ptr>
		class stream {
		public:
			// DOCME
			typedef T value_type;

		protected:
			// DOCME
			const Pointer<iterators::iterator<T> > source;

		public:
			// DOCME
			stream( const Pointer<iterators::iterator<T> >& source );

			// Intermediate Operations

			// DOCME
			virtual Pointer<stream<T, Pointer> > filter( std::function<bool( const T& )> filter );

			// DOCME
			virtual Pointer<stream<T, Pointer> > limit( size_t limit );

			// DOCME
			// TODO: Make sure autodeduction works at all
			template<class Out>
			Pointer<stream<Out, Pointer> > map( std::function<Out( const T& )> mapper );

			// DOCME
			virtual Pointer<stream<T, Pointer> > peek( std::function<void( const T& )> peeker );

			// DOCME
			virtual Pointer<stream<T, Pointer> > skip( size_t skip );

			// Terminal Operations

			// DOCME
			virtual bool all_match( std::function<bool( const T& )> filter );

			// DOCME
			virtual bool any_match( std::function<bool( const T& )> filter );

			// DOCME
			virtual bool none_match( std::function<bool( const T& )> filter );

			// DOCME
			template<class Container>
			Container collect( const Pointer<collectors::collector<T, Container> >& collector = streams::to_vector<T, Pointer> );

			// DOCME
			// TESTME
			std::vector<T> collect();

			// DOCME
			virtual size_t count();

			// DOCME
			virtual T find_first( std::function<bool( const T& )> filter );

#if CPPSTREAMS_CPP17
			// DOCME
			virtual std::optional<T> find_first_opt( std::function<bool( const T& )> filter );
#endif

			// DOCME
			// TESTME
			virtual void for_each( std::function<void( const T& )> consumer );

			// DOCME
			virtual T max( std::function<bool( const T&, const T& )> comparator = std::less<T>() );

#if CPPSTREAMS_CPP17
			// DOCME
			virtual std::optional<T> max_opt( std::function<bool( const T&, const T& )> comparator = std::less<T>() );
#endif

			// DOCME
			virtual T min( std::function<bool( const T&, const T& )> comparator = std::less<T>() );

#if CPPSTREAMS_CPP17
			// DOCME
			virtual std::optional<T> min_opt( std::function<bool( const T&, const T& )> comparator = std::less<T>() );
#endif

			// DOCME
			// TODO: Make this method preferred
			template<class Out>
			Out reduce( std::function<Out( const T&, const Out& )> accumulator, Out identity = Out() );

			// DOCME
			template<class Out>
			Out reduce( std::function<void( const T&, Out& )> accumulator, Out identity = Out() );
		};

		// ==============================================================================
		// Implementation
		// ==============================================================================

		template<class T, template<class> class Pointer>
		stream<T, Pointer>::stream( const Pointer<iterators::iterator<T> >& source ) :
			source( source ) {}

		template<class T, template<class> class Pointer>
		Pointer<stream<T, Pointer> > stream<T, Pointer>::filter( std::function<bool( const T& )> filter ) {
			return Pointer<stream<T, Pointer> >( new stream<T, Pointer>( Pointer<iterators::iterator<T> >( new iterators::transformation_iterators::filter_iterator<T, Pointer>( source, filter ) ) ) );
		}

		template<class T, template<class> class Pointer>
		Pointer<stream<T, Pointer> > stream<T, Pointer>::limit( size_t limit ) {
			return Pointer<stream<T, Pointer> >( new stream<T, Pointer>( Pointer<iterators::iterator<T> >( new iterators::transformation_iterators::limit_iterator<T, Pointer>( source, limit ) ) ) );
		}

		template<class T, template<class> class Pointer>
		template<class Out>
		Pointer<stream<Out, Pointer> > stream<T, Pointer>::map( std::function<Out( const T& )> mapper ) {
			return Pointer<stream<Out, Pointer> >( new stream<Out, Pointer>( Pointer<iterators::iterator<Out> >( new iterators::transformation_iterators::map_iterator<T, Out, Pointer>( source, mapper ) ) ) );
		}

		template<class T, template<class> class Pointer>
		Pointer<stream<T, Pointer>> stream<T, Pointer>::peek( std::function<void( const T& )> peeker ) {
			return Pointer<stream<T, Pointer> >( new stream<T, Pointer>( Pointer<iterators::iterator<T> >( new iterators::transformation_iterators::peek_iterator<T, Pointer>( source, peeker ) ) ) );
		}

		template<class T, template<class> class Pointer>
		Pointer<stream<T, Pointer> > stream<T, Pointer>::skip( size_t skip ) {
			return Pointer<stream<T, Pointer> >( new stream<T, Pointer>( Pointer<iterators::iterator<T> >( new iterators::transformation_iterators::skip_iterator<T, Pointer>( source, skip ) ) ) );
		}

		template<class T, template<class> class Pointer>
		bool stream<T, Pointer>::all_match( std::function<bool( const T& )> filter ) {
			while ( source->has_element() ) {
				if ( !filter( source->fetch() ) ) {
					return false;
				}
			}

			return true;
		}

		template<class T, template<class> class Pointer>
		bool stream<T, Pointer>::any_match( std::function<bool( const T& )> filter ) {
			while ( source->has_element() ) {
				if ( filter( source->fetch() ) ) {
					return true;
				}
			}

			return false;
		}

		template<class T, template<class> class Pointer>
		bool stream<T, Pointer>::none_match( std::function<bool( const T& )> filter ) {
			return !any_match( filter );
		}

		template<class T, template<class> class Pointer>
		template<class Container>
		Container stream<T, Pointer>::collect( const Pointer<collectors::collector<T, Container> >& collector ) {
			return reduce( collector->accumulator(), collector->create_instance() );
		}

		template<class T, template<class> class Pointer>
		std::vector<T> stream<T, Pointer>::collect() {
			return collect( streams::to_vector<T, typename std::vector<T>::allocator_type, Pointer>() );
		}

		template<class T, template<class> class Pointer>
		size_t stream<T, Pointer>::count() {
			size_t count( 0 );

			while ( source->has_element() ) {
				source->fetch();
				++count;
			}

			return count;
		}

		template <class T, template <class> class Pointer>
		T stream<T, Pointer>::find_first( std::function<bool( const T& )> filter ) {
			// Loop until we find an element or throw
			while ( true ) {
				if ( filter( source->peek() ) ) {
					return source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}
		}

#if CPPSTREAMS_CPP17
		template <class T, template <class> class Pointer>
		std::optional<T> stream<T, Pointer>::find_first_opt( std::function<bool( const T& )> filter ) {
			while ( source->has_element() ) {
				if ( filter( source->peek() ) ) {
					return source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}

			return std::nullopt;
		}
#endif

		template<class T, template<class> class Pointer>
		void stream<T, Pointer>::for_each( std::function<void( const T& )> consumer ) {
			while ( source->has_element() ) {
				consumer( source->fetch() );
			}
		}

		template<class T, template<class> class Pointer>
		T stream<T, Pointer>::max( std::function<bool( const T&, const T& )> comparator ) {
			T largest( source->fetch() );

			while ( source->has_element() ) {
				if ( comparator( largest, source->peek() ) ) {
					largest = source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}

			return largest;
		}

#if CPPSTREAMS_CPP17
		template<class T, template<class> class Pointer>
		std::optional<T> stream<T, Pointer>::max_opt( std::function<bool( const T&, const T& )> comparator ) {
			if ( !source->has_element() )
				return std::nullopt;

			T largest( source->fetch() );

			while ( source->has_element() ) {
				if ( comparator( largest, source->peek() ) ) {
					largest = source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}

			return largest;
		}
#endif

		template<class T, template<class> class Pointer>
		T stream<T, Pointer>::min( std::function<bool( const T&, const T& )> comparator ) {
			T smallest( source->fetch() );

			while ( source->has_element() ) {
				if ( comparator( source->peek(), smallest ) ) {
					smallest = source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}

			return smallest;
		}

#if CPPSTREAMS_CPP17
		template<class T, template<class> class Pointer>
		std::optional<T> stream<T, Pointer>::min_opt( std::function<bool( const T&, const T& )> comparator ) {
			if ( !source->has_element() )
				return std::nullopt;

			T smallest( source->fetch() );

			while ( source->has_element() ) {
				if ( comparator( source->peek(), smallest ) ) {
					smallest = source->fetch();
				} else {
					// Fetch to advance the iterator
					source->fetch();
				}
			}

			return smallest;
		}
#endif

		template<class T, template<class> class Pointer>
		template<class Out>
		Out stream<T, Pointer>::reduce( std::function<Out( const T&, const Out& )> accumulator, Out identity ) {
			Out result( identity );

			while ( source->has_element() ) {
				result = accumulator( source->fetch(), result );
			}

			return result;
		}

		template<class T, template<class> class Pointer>
		template<class Out>
		Out stream<T, Pointer>::reduce( std::function<void( const T&, Out& )> accumulator, Out identity ) {
			Out result( identity );

			while ( source->has_element() ) {
				accumulator( source->fetch(), result );
			}

			return result;
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
