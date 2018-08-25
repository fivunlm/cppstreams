//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H

// Includes
#include <functional>
#include <memory>

#include "cppstreams/iterator.h"

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
			// TESTME
			virtual Pointer<stream<T, Pointer> > filter( std::function<bool( const T& )> filter );

			// DOCME
			// TESTME
			template<class Out>
			Pointer<stream<Out, Pointer> > map( std::function<Out( const T& )> mapper );

			// Terminal Operations

			// DOCME
			// TESTME
			virtual bool all_match( std::function<bool( const T& )> filter );

			// DOCME
			// TESTME
			virtual bool any_match( std::function<bool( const T& )> filter );

			// DOCME
			// TESTME
			virtual bool none_match( std::function<bool( const T& )> filter );

			// DOCME
			// TESTME
			virtual size_t count();

			// DOCME
			// TESTME
			virtual void for_each( std::function<void( const T& )> consumer );
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
		template<class Out>
		Pointer<stream<Out, Pointer> > stream<T, Pointer>::map( std::function<Out( const T& )> mapper ) {
			return Pointer<stream<Out, Pointer> >( new stream<Out, Pointer>( Pointer<iterators::iterator<Out> >( new iterators::transformation_iterators::map_iterator<T, Out, Pointer>( source, filter ) ) ) );
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
		size_t stream<T, Pointer>::count() {
			size_t count( 0 );

			while ( source->has_element() ) {
				source->fetch();
				++count;
			}

			return count;
		}

		template<class T, template<class> class Pointer>
		void stream<T, Pointer>::for_each( std::function<void( const T& )> consumer ) {
			while ( source->has_element() ) {
				consumer( source->fetch() );
			}
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_STREAMS_STREAM_H
