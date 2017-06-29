//
// Created by FernandoDamian on 7/16/2016.
//

#ifndef CPPSTREAMS_STREAM_H
#define CPPSTREAMS_STREAM_H


#include <list>
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
    int iIndex;
    enum Type eType;

    static PipelineOperation makeOperation(int iIndex, enum Type eType) {
        PipelineOperation sAux;
        sAux.iIndex = iIndex;
        sAux.eType = eType;
        return sAux;
    }
};


template<typename T>
class Stream {

public:
    Stream(const std::list<T> &lOriginal) : originalList(lOriginal) {}

    Stream<T>& map(std::function<T(const T &)> func);

    Stream<T>& filter(std::function<bool(const T &)> func);

    std::list<T> collect(int iLimit = -1);

    T sum(T initiator = 0);

    T findFirst(std::function<bool(const T &)> func, T defaultValue = 0);

    static Stream<T> makeStream(std::list<T> &lOriginal);

private:

    std::vector<std::function<T(const T &)> > mapOperations;
    std::vector<std::function<bool(const T &)> > filterOperations;

    std::list<PipelineOperation> pipeline;
    const std::list<T> & originalList;
};

template<typename T>
Stream<T> Stream<T>::makeStream(std::list<T> &lOriginal) {
    Stream<T> oStream(lOriginal);
    return oStream;
}

template<typename T>
Stream<T> &Stream<T>::map(std::function<T(const T &)> func) {
    mapOperations.push_back(func);
    pipeline.push_back(PipelineOperation::makeOperation(mapOperations.size() - 1, MAP));
    return *this;
}

template<typename T>
Stream<T> &Stream<T>::filter(std::function<bool(const T &)> func) {
    filterOperations.push_back(func);
    pipeline.push_back(PipelineOperation::makeOperation(filterOperations.size() - 1, FILTER));
    return *this;
}

template<typename T>
std::list<T> Stream<T>::collect(int iLimit) {

    std::list<T> lResult;
    iLimit = iLimit > 0 ? iLimit : originalList.size();

    // Loop through each input value (ONLY ONCE!) and operate if needed
    for (const auto& value : originalList) {

        // if we reach the limit, just break
        if (lResult.size() == iLimit) break;

        T aux = value; // T object should override operator equals
        bool bLastFilterResult = true;

        // Go through each operation on the pipeline and execute the lambdas
        for (const auto& operation : pipeline) {

            switch (operation.eType) {
                case MAP:
                    aux = mapOperations[operation.iIndex](aux);
                    break;
                case FILTER:
                    bLastFilterResult = filterOperations[operation.iIndex](aux);
                    break;
            }

        }
        // So if the filter filters there is no reason to keep this value on the output
        if (!bLastFilterResult)
            continue;

        lResult.push_back(aux);
    }
    return lResult;
}

template<typename T>
T Stream<T>::findFirst(std::function<bool(const T &)> func, T defaultValue) {
    std::list<T> lResult = collect();
    for (const auto& value : originalList ) {
        if (func(value))
            return value;
    }
    return defaultValue;
}

template<typename T>
T Stream<T>::sum(T initiator) {
    std::list<T> lResult = collect();
    return std::accumulate(lResult.begin(), lResult.end(), initiator);
}


#endif //CPPSTREAMS_STREAM_H
