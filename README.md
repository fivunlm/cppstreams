# Java 8 Streams C++ port

This is a very simple implementation of the behaviour of Java 8 Streams.

The idea is to have a strema class that can handle **filter**, **map** and **collect** methods. It should operate over STL containers. And it would let you chain operations in a efficient way by pipelining them.

This STL containers have been tested:
* list
* vector
* set

## Usage

To use it just create a stream object, it needs two template arguments. First the stream contained object type, then the original container type. here is an example using a list of ints:

<code> Stream<int, std::list<int> > oStream(testList); </code>

or you can just use makeStream static method:

<code> Stream<int, std::list<int> >::makeStream(testList) </code>

Then chain as many *map* and/or *filter* as needed:

<code> 
oStream.filter([](const int &iValue) { return iValue % 2 == 0; })<br>
       .map([](const int &iValue) { return iValue * 2; })<br>
       .map([](const int &iValue) { return iValue + 3; })
</code>

And finally use the method *collect*. It receives an optional limit parameter to get a restricted set of the original list

<code> .collect()</code>

*collect* will return a new list with the applied functions.

There are several other methods like *sum* to accumulate the objects of the stream, *findFirst* to find first occurrence given a predicate. And more are coming.

## Motivation

For the full story check this [Medium post](https://medium.com/@lopez.fernando.damian/java-8-streams-c-port-9aaaed28b81a#.qml1he9ez).

## TODO

There are so many things to add and improve, here are some:

* Test it with containers of complex objects and structs
* Add *reduce* method
* Add *forEach*
* Add *findAny*
* Infinite streams
* Check performance


