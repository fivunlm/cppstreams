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


template<class T>
class Stream {

public:
    Stream(std::list<T> &lOriginal) : m_lOriginalList(lOriginal) {}

    Stream<T> &map(std::function<T(const T &)> func);

    Stream<T> &filter(std::function<bool(const T &)> func);

    std::list<T> collect(int iLimit = -1);

    T sum(T initiator = 0);

    T findFirst(std::function<bool(const T &)> func, T defaultValue = 0);

    static Stream<T> makeStream(std::list<T> &lOriginal);

private:

    std::vector<std::function<T(const T &)> > m_vMapOperations;
    std::vector<std::function<bool(const T &)> > m_vFilterOperations;

    std::list<PipelineOperation> m_lPipeline;
    std::list<T> &m_lOriginalList;
};

template<class T>
Stream<T> Stream<T>::makeStream(std::list<T> &lOriginal) {
    Stream<T> oStream(lOriginal);
    return oStream;
}

template<class T>
Stream<T> &Stream<T>::map(std::function<T(const T &)> func) {
    m_vMapOperations.push_back(func);
    m_lPipeline.push_back(PipelineOperation::makeOperation(m_vMapOperations.size() - 1, MAP));
    return *this;
}

template<class T>
Stream<T> &Stream<T>::filter(std::function<bool(const T &)> func) {
    m_vFilterOperations.push_back(func);
    m_lPipeline.push_back(PipelineOperation::makeOperation(m_vFilterOperations.size() - 1, FILTER));
    return *this;
}

template<class T>
std::list<T> Stream<T>::collect(int iLimit) {

    std::list<T> lResult;
    iLimit = iLimit > 0 ? iLimit : m_lOriginalList.size();

    // Loop through each input value (ONLY ONCE!) and operate if needed
    for (typename std::list<T>::iterator itOriginal = m_lOriginalList.begin();
         itOriginal != m_lOriginalList.end();
         ++itOriginal) {

        // if we reach the limit, just break
        if (lResult.size() == iLimit) break;

        T aux = *itOriginal; // T object should override operator equals
        bool bLastFilterResult = true;

        // Go through each operation on the pipeline and execute the lambdas
        for (std::list<PipelineOperation>::iterator itOperation = m_lPipeline.begin();
             itOperation != m_lPipeline.end() && bLastFilterResult;
             ++itOperation) {

            switch (itOperation->eType) {
                case MAP:
                    aux = m_vMapOperations[itOperation->iIndex](aux);
                    break;
                case FILTER:
                    bLastFilterResult = m_vFilterOperations[itOperation->iIndex](aux);
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

template<class T>
T Stream<T>::findFirst(std::function<bool(const T &)> func, T defaultValue) {
    std::list<T> lResult = collect();
    for (typename std::list<T>::iterator itOriginal = m_lOriginalList.begin();
         itOriginal != m_lOriginalList.end();
         ++itOriginal) {
        if (func(*itOriginal))
            return *itOriginal;
    }
    return defaultValue;
}

template<class T>
T Stream<T>::sum(T initiator) {
    std::list<T> lResult = collect();
    return std::accumulate(lResult.begin(), lResult.end(), initiator);
}


#endif //CPPSTREAMS_STREAM_H
