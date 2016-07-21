#include <iostream>
#include <list>
#include <assert.h>
#include "streams/Stream.h"

using namespace std;

void printListOfInts(list<int> &lToPrint) {
    for (list<int>::iterator it = lToPrint.begin(); it != lToPrint.end(); ++it)
        cout << *it << " ";
}

int main() {
    cout << "CPP Stream Test!" << endl;

    list<int> lTestList;
    lTestList.push_back(0);
    lTestList.push_back(1);
    lTestList.push_back(2);
    lTestList.push_back(3);
    lTestList.push_back(4);
    lTestList.push_back(5);
    lTestList.push_back(6);
    lTestList.push_back(7);
    lTestList.push_back(8);
    lTestList.push_back(9);


    cout << "------------------------------------------------" << endl;
    cout << "Test get a list with the double of even values" << endl;
    Stream<int> oStream(lTestList);

    list<int> lTest1 = oStream.filter([](const int &iValue) { return iValue % 2 == 0; })
            .map([](const int &iValue) { return iValue * 2; })
            .collect();
    printListOfInts(lTest1);
    assert(lTest1.size() == 5);
    assert(lTest1.front() == 0);
    lTest1.pop_front();
    assert(lTest1.front() == 4);
    lTest1.pop_front();
    assert(lTest1.front() == 8);
    lTest1.pop_front();
    assert(lTest1.front() == 12);
    lTest1.pop_front();
    assert(lTest1.front() == 16);
    lTest1.pop_front();
    cout << endl << "OK" << endl;
    return 0;
}