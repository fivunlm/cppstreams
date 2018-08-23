//
// Copyright (c) 2016-2018 Fernando Damian Lopez
// Copyright (c) 2018 Yannick Schinko
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
//
#ifndef CPPSTREAMS_STREAM_H
#define CPPSTREAMS_STREAM_H

#include <vector>
#include <functional>
#include <iostream>
#include <numeric>


template<typename T, typename Container>
class Stream {

public:
    explicit Stream (const Container & original) : originalContainer(original) {}

    Stream<T, Container>& map(std::function<T(const T &)> func);

    Stream<T, Container>& filter(std::function<bool(const T &)> func);

    Container collect(int limit = -1);

    T sum(T startValue = 0);

    T findFirst(std::function<bool(const T &)> func, T defaultValue);

    static Stream<T, Container> makeStream(const Container& original);

private:
    // Pipeline operation types
    enum class Type {
        Map,
        Filter
    };

    struct Operation {
        int index;
        enum Type type;

        static Operation makeOperation(int index, enum Type type) {
            Operation operation;
            operation.index = index;
            operation.type = type;
            return operation;
        }
    };

    std::vector<std::function<T(const T &)> > _mapOperations;
    std::vector<std::function<bool(const T &)> > _filterOperations;

    std::vector<Operation> _pipeline;
    const Container & originalContainer;
};

template<typename T, typename Container>
Stream<T, Container> Stream<T, Container>::makeStream(const Container& original) {
    Stream<T, Container> oStream(original);
    return oStream;
}

template<typename T, typename Container>
Stream<T, Container> & Stream<T, Container>::map(std::function<T(const T &)> func) {
    _mapOperations.push_back(func);
    _pipeline.push_back(Operation::makeOperation(_mapOperations.size() - 1, Type::Map));
    return *this;
}

template<typename T, typename Container>
Stream<T, Container> & Stream<T, Container>::filter(std::function<bool(const T &)> func) {
    _filterOperations.push_back(func);
    _pipeline.push_back(Operation::makeOperation(_filterOperations.size() - 1, Type::Filter));
    return *this;
}

template<typename T, typename Container>
Container Stream<T, Container>::collect(int limit) {

    Container result;
    limit = limit > 0 ? limit : originalContainer.size();

    // Loop through each input value (ONLY ONCE!) and operate if needed
    for (const auto & value : originalContainer) {

        // if we reach the limit, just break
        if (result.size() == limit) break;

        T aux = value; // T object should override operator equals
        auto wasFiltered = true;

        // Go through each operation on the pipeline and execute the lambdas
        for (const auto& operation : _pipeline) {

            switch (operation.type) {
                case Type::Map:
                    aux = _mapOperations[operation.index](aux);
                    break;
                case Type::Filter:
                    wasFiltered = _filterOperations[operation.index](aux);
                    break;
            }

        }
        // So if the filter filters there is no reason to keep this value on the output
        if (!wasFiltered)
            continue;

        result.insert(result.end(), aux);
    }
    return result;
}

template<typename T, typename Container>
T Stream<T, Container>::findFirst(std::function<bool(const T &)> func, T defaultValue) {
    Container lResult = collect();
    for (const auto& value : originalContainer ) {
        if (func(value))
            return value;
    }
    return defaultValue;
}

template<typename T, typename Container>
T Stream<T, Container>::sum(T startValue) {
    Container collected = collect();
    return std::accumulate(collected.begin(), collected.end(), startValue);
}


#endif //CPPSTREAMS_STREAM_H
