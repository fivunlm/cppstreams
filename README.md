# Java 8 Streams C++ port

This is a very simple implementation of the behaviour of Java 8 Streams.

As a first stage I wanted to create a stream class that can handle **std::list** with **filter**, **map** and **collect** methods. It should operate over standard lists. And it would let you chain operations in a efficient way by pipelining them.

## Usage

To use it just create a stream object from a list:

<code> Stream<int> oStream(lTestList); </code>

Then apply as many *map* and/or *filter* as needed:

<code> 
oStream.filter([](const int &iValue) { return iValue % 2 == 0; })<br>
       .map([](const int &iValue) { return iValue * 2; })<br>
       .map([](const int &iValue) { return iValue + 3; })
</code>

And finally use the method *collect*. It receives an optional limit parameter to get a restricted set of the original list

<code> .collect()</code>

*collect* will return a new list with the applyed functions.

## Motivation

For the full story check this [Medium post](https://medium.com/@lopez.fernando.damian/la-biblioteca-no-levanta-b536a8e53529#.9hp7uvvrv).

## TODO

There are so many things to add and improve, here are some:

* Work with standard vector
* Work with standard map
* Work with standard set
* Work with standard queue?
* Test it with real objects and structs
* Add more tests.
* Add *reduce* method
* Add *sum*
* Add *forEach*
* Add *findFirst* and *findAny*
* Infinite streams
* Check performance

