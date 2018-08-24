//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H
#define CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H

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
			 * Returns the next value from the underlying container.
			 *
			 * The method is supposed to first fetch the value the iterator is currently pointing at and then
			 * advance the pointer to the next object.
			 *
			 * <strong>WARNING</strong>:
			 * Undefined behavior if <code>has_next()</code> returns <code>false</code>!<br>
			 * Make sure to always check that before calling this method!
			 */
			virtual const T next() = 0;

			/**
			* Returns the next value from the underlying container without changing the iterator pointer.
			*
			* The method just fetches the value the iterator is currently pointing at and doesn't advance the
			* pointer to the next object.
			*
			* <strong>WARNING</strong>:
			* Undefined behavior if <code>has_next()</code> returns <code>false</code>!<br>
			* Make sure to always check that before calling this method!
			*/
			virtual const T peek() const noexcept = 0;

			/**
			 * Checks if there is a next value to return.
			 *
			 * This method doesn't change the internal state of the iterator and is safe to call.<br>
			 * <strong>ALWAYS</strong> call this before <code>next()</code>. (And only call this if this method
			 * returns true!
			 */
			virtual bool has_next() const noexcept = 0;
		};
	}
}

#endif // #ifndef CPPSTREAMS_INCLUDE_GUARD_CPPSTREAMS_ITERATORS_ITERATOR_H