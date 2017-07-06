//
// Created by FernandoDamian on 7/16/2016.
//

#ifndef CPPSTREAMS_STREAM_H
#define CPPSTREAMS_STREAM_H

#include <vector>
#include <functional>
#include <iostream>
#include <numeric>

// Pipeline operation types
enum Type {
    MAP,
    FILTER
};

struct PipelineOperation {
    int index;
    enum Type type;

    static PipelineOperation makeOperation(int index, enum Type type) {
        PipelineOperation operation;
        operation.index = index;
        operation.type = type;
        return operation;
    }
};


template<typename T, typename Container>
class Stream {

public:
    Stream(const Container &original) : originalContainer(original) {}

    Stream<T, Container>& map(std::function<T(const T &)> func);

    Stream<T, Container>& filter(std::function<bool(const T &)> func);

    Container collect(int limit = -1);

    T sum(T startValue = 0);

    T findFirst(std::function<bool(const T &)> func, T defaultValue);

    static Stream<T, Container> makeStream(const Container& original);

private:

    std::vector<std::function<T(const T &)> > mapOperations;
    std::vector<std::function<bool(const T &)> > filterOperations;

    std::vector<PipelineOperation> pipeline;
    const Container & originalContainer;
};

template<typename T, typename Container>
Stream<T, Container> Stream<T, Container>::makeStream(const Container& original) {
    Stream<T, Container> oStream(original);
    return oStream;
}

template<typename T, typename Container>
Stream<T, Container> &Stream<T, Container>::map(std::function<T(const T &)> func) {
    mapOperations.push_back(func);
    pipeline.push_back(PipelineOperation::makeOperation(mapOperations.size() - 1, MAP));
    return *this;
}

template<typename T, typename Container>
Stream<T, Container> &Stream<T, Container>::filter(std::function<bool(const T &)> func) {
    filterOperations.push_back(func);
    pipeline.push_back(PipelineOperation::makeOperation(filterOperations.size() - 1, FILTER));
    return *this;
}

template<typename T, typename Container>
Container Stream<T, Container>::collect(int limit) {

    Container result;
    limit = limit > 0 ? limit : originalContainer.size();

    // Loop through each input value (ONLY ONCE!) and operate if needed
    for (const auto& value : originalContainer) {

        // if we reach the limit, just break
        if (result.size() == limit) break;

        T aux = value; // T object should override operator equals
        bool wasFiltered = true;

        // Go through each operation on the pipeline and execute the lambdas
        for (const auto& operation : pipeline) {

            switch (operation.type) {
                case MAP:
                    aux = mapOperations[operation.index](aux);
                    break;
                case FILTER:
                    wasFiltered = filterOperations[operation.index](aux);
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
