//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018-2019 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H

#include <stdexcept>

namespace cppstreams {
	namespace iterators {
		/**
		 * Abstract iterator class designed to provide a generic interface for all kinds of containers.
		 *
		 * To support more containers, we just need to add more subclasses.
		 */
		template<class T>
		class iterator {
		public:
			// DOCME
			typedef T value_type;

			/**
			 * Returns the next element from the underlying container.
			 *
			 * The method is supposed to first fetch the element the iterator is currently pointing at and then
			 * advance the pointer to the next element.
			 *
			 * @returns The element the pointer of the underlying container iterator points at.
			 * @throws std::range_error if <code>has_element()</code> returns <code>false</code>!
			 */
			virtual const T fetch() = 0;

			/**
			* Returns the next element from the underlying container without changing the iterator pointer.
			*
			* The method just fetches the element the iterator is currently pointing at and doesn't advance the
			* pointer to the next element.
			*
			* @returns The element the pointer of the underlying container iterator points at.
			* @throws std::range_error if <code>has_element()</code> returns <code>false</code>!
			*/
			virtual const T peek() = 0;

			/**
			 * Checks if there is a next element to return.
			 *
			 * This method doesn't change the internal state of the iterator and is safe to call.
			 *
			 * <strong>ALWAYS</strong> call this before <code>fetch()</code> or <code>peek()</code>. (And only call
			 * these methods if this method returns <code>true</code>!)
			 *
			 * @returns <code>true</code> if the pointer points at a valid element, <code>false</code> if not.
			 */
			virtual bool has_element() = 0;

		protected:
			/**
			 * This is a internal helper method designed throw an expection when the iterator is at the end and
			 * it is tried to retrieve an elemement.
			 *
			 * Just checks if <code>has_element()</code> returns <code>true</code>.<br>
			 * If it returns <code>false</code> however, it throws a <code>std::range_error</code> with the message:
			 * <code>"The iterator doesn't have any more elements"</code>
			 *
			 * @throws std::range_error if <code>has_element()</code> returns <code>false</code>!
			 */
			virtual void check_state();
		};

		// ==============================================================================
		// Implementation
		// ==============================================================================

		template<class T>
		void iterator<T>::check_state() {
			if ( !has_element() )
				throw std::range_error( "The iterator doesn't have any more elements" );
		}
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H