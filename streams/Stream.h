//
// Created by FernandoDamian on 7/16/2016.
//

#ifndef CPPSTREAMS_STREAM_H
#define CPPSTREAMS_STREAM_H


#include <list>
#include <vector>
#include <functional>
#include <iostream>

template<class T>
class Stream {

public:
    Stream( std::list<T> & list ): originalList(list) { }
    Stream( std::vector<T> & vector ) { }

    Stream<T> & map(std::function<T (const T&)>  func);
    Stream<T> & filter(std::function<T (const T&)> func);
    std::list<T> limit(int limit);

private:
    enum Operation {
        MAP,
        FILTER
    };

    std::vector<std::function<T (const T&)> > m_vMapOperations;
    // TODO: Replace this pair for something more meaningful
    std::list<std::pair<int, enum Operation> > m_lPipeline;
    std::list<T> originalList;
};

template<class T>
Stream<T> &Stream<T>::map(std::function<T(const T &)> func) {
    m_vMapOperations.push_back(func);
    m_lPipeline.push_back(std::make_pair(m_vMapOperations.size()-1, MAP));
    return *this;
}

template<class T>
Stream<T> &Stream<T>::filter(std::function<T(const T &)> func) {
    // TODO: Implement this
    return *this;
}

template<class T>
std::list<T> Stream<T>::limit(int limit) {

    std::list<T> resultList;
    // Loop through each input value (ONLY ONCE!) and operate if needed
    for(typename std::list<T>::iterator itOriginal = originalList.begin();
            itOriginal != originalList.end();
            ++itOriginal){

        // AS we are on limit function check it an break if we got to the limit
        if( resultList.size() == limit) break;

        T aux = *itOriginal;
        // Go through each operation and execute it
        for(typename std::list<std::pair<int, enum Operation> >::iterator itOperation = m_lPipeline.begin();
                itOperation != m_lPipeline.end();
                ++itOperation){

            switch(itOperation->second){
                case MAP:
                    aux = m_vMapOperations[itOperation->first](aux);
                    break;
            }

        }
        resultList.push_back(aux);
    }
    return resultList;
}


#endif //CPPSTREAMS_STREAM_H
