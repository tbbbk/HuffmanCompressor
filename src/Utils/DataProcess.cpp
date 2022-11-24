//
// Created by TBK on 2022/11/24.
//

#ifndef __DATAPROCESS_CPP__
#define __DATAPROCESS_CPP__

#include <map>
#include <iostream>
#include "Node.h"

using namespace std;

map<int, int> static CountData(char Buffer[], int size) {
    map<int, int> counters;
    for (int i = 0, tmp; i < size; i++) {
        tmp = (int) Buffer[i];
        if (!counters.count(tmp)) {
            counters.insert({tmp, 1});
        } else {
            counters[tmp]++;
        }
    }
    return counters;
}

Node static *CreateHuffmanTree(map<int, int> b) {
    Node a[3] = {1, 2, 3};
    return a;
}

#endif