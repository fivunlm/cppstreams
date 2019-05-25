# Java 8 Streams C++ port [![Build Status](https://travis-ci.org/fivunlm/cppstreams.svg?branch=master)](https://travis-ci.org/fivunlm/cppstreams)

This is an e implementation of the behaviour of Java 8 Streams.

The idea is to have a stream class that can handle **filter**, **map** and **collect** methods. It should operate over STL containers. And it would let you
chain operations in a efficient way by pipelining them.

These STL containers have been tested:
* `std::array`
* `std::deque`
* `std::forward_list`
* `std::list`
* `std::map`
* `std::multimap`
* `std::multiset`
* `std::set`
* `std::string` (iterating over the `char`s)
* `std::unordered_map`
* `std::unordered_multimap`
* `std::unordered_multiset`
* `std::unordered_set`
* `std::vector`

Additionally normal arrays work too.

In fact every container that supports [`std::begin`](https://en.cppreference.com/w/cpp/iterator/begin) and
[`std::end`](https://en.cppreference.com/w/cpp/iterator/begin) will work.  
For example all `boost` containers will work. And all containers implementing `begin()` and `end()`. Or all containers that have a template specialization of
`std::begin` and `std::end`.  
In short if you can iterate over the container, it'll work.  
And in the very worst case you can also create your own implementation of `cppstreams::iterators::iterator<T>` to add support for your particular container.

## Cloning

Since this repo is recursive, you need to clone it recursively

```sh
git clone --recursive https://github.com/fivunlm/cppstreams.git
```

If you forgot to do that, you can download the submodules later by running

```sh
git submodule update --init --recursive
```

### Hooks

This repo also provides a few simple hooks to make working with submodules easier. While it is not necessary to do this step, it is recommended.

```sh
cp -va .hooks/* .git/hooks/
```

## Building

This project uses gradle for building. The nice thing about gradle is that you only need to have Java (and a C++ compiler (Needs support for C++11) of your
choice) installed.  
Building is super straight forward:

```sh
./gradlew build
```

This will build the project, all its dependencies and perform the test.

Use the following to just build the project and all its dependencies without performing the tests.

```sh
./gradlew assemble
```

### Specifying the C++ Version

If you want to compile this project with a different C++ version than which is the default of your compiler, you can do it in several ways. It is passed
directly to the compiler. So if you specify the value `c++1y` and you're compiling with gcc/g++, then the code will get compiled with the additional flag
`-std=c++1y`. So be sure to only specify the version and not the whole flag.  
Ordered from lowest to highest priority:

- Set `cxxVersion` in your `gradle.properties` file (check gradle documentation on where it goes. Typically it's located under `~/.gradle/gradle.properties`):  
  ```
  cxxVersion=c++17
  ```
- Add the `-PcxxVersion=` flag to the gradle command line:  
  ```sh
  ./gradlew -PcxxVersion=c++17 assemble
  ```
- Export the environment variable `CXX_VERSION`:  
  ```sh
  export CXX_VERSION=c++17
  ```
- Specify the environment variable `CXX_VERSION` on the gradle command line:  
  ```sh
  CXX_VERSION=c++17 ./gradlew assemble
  ```

## Usage

Coming Soon&trade;

## Motivation

For the full story check this [Medium post](https://medium.com/@lopez.fernando.damian/java-8-streams-c-port-9aaaed28b81a#.qml1he9ez).

## TODO

There are a lot of things still to do:

* Add `find_any` method
* Add `sort` method
* Infinite streams
* Performance analysis
* Parallel streams
