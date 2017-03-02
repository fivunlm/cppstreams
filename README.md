# Java 8 Streams C++ port

This is a very simple implementation of the behaviour of Java 8 Streams.

As a first stage I wanted to create a stream class that can handle **std::list** with **filter**, **map** and **collect** methods. It should operate over standard lists. And it would let you chain operations in a efficient way by pipelining them.

## Usage

To use it just create a stream object from a list:

<code> Stream<int> oStream(lTestList); </code>

or you can just use makeStream static method:

<code> Stream<int>::makeStream(lTestList) </code>

Then apply as many *map* and/or *filter* as needed:

<code> 
oStream.filter([](const int &iValue) { return iValue % 2 == 0; })<br>
       .map([](const int &iValue) { return iValue * 2; })<br>
       .map([](const int &iValue) { return iValue + 3; })
</code>

And finally use the method *collect*. It receives an optional limit parameter to get a restricted set of the original list

<code> .collect()</code>

*collect* will return a new list with the applied functions.

## Motivation

For the full story check this [Medium post](https://medium.com/@lopez.fernando.damian/java-8-streams-c-port-9aaaed28b81a#.qml1he9ez).

## TODO

There are so many things to add and improve, here are some:

* Work with standard vector
* Work with standard map
* Work with standard set
* Work with standard queue?
* Test it with containers of complex objects and structs
* Add *reduce* method
* Add *forEach*
* Add *findAny*
* Infinite streams
* Check performance
* Improve build process

