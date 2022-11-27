//
// Created by TBK on 2022/11/24.
//

#ifndef __DATAPROCESS_CPP__
#define __DATAPROCESS_CPP__

#include <map>
#include <iostream>
#include <queue>
#include <cstring>
#include "Node.h"

using namespace std;

priority_queue<Node> static CountData(char Buffer[], int size) {
    map<int, int> counters;
    priority_queue<Node> q;
    for (int i = 0, tmp; i < size; i++) {
        tmp = (int) Buffer[i];
        if (!counters.count(tmp)) {
            counters.insert({tmp, 1});
        } else {
            counters[tmp]++;
        }
    }
    auto it = counters.begin();
    while (it != counters.end()) {
        q.push(*(new Node(it->first, it->second)));
        it++;
    }
    return q;
}

typedef pair<Node *, int> PNI;

PNI static CreateHuffmanTree(priority_queue<Node> q) {
    Node *result = new Node[2 * q.size() + 1];
    Node VOID;
    result[0] = VOID;
    int idx = 0;
    while (true) {
        auto FirstNode = q.top();
        q.pop();
        auto SecondNode = q.top();
        q.pop();
        FirstNode.setIndex(++idx);
        result[idx] = FirstNode;
        SecondNode.setIndex(++idx);
        result[idx] = SecondNode;
        // ��Ҷ�ӽڵ�
        if (FirstNode.getL() != 0 && FirstNode.getR() != 0) {
            result[FirstNode.getL()].setP(FirstNode.getIndex());
            result[FirstNode.getR()].setP(FirstNode.getIndex());
        }
        if (SecondNode.getL() != 0 && SecondNode.getR() != 0) {
            result[SecondNode.getL()].setP(SecondNode.getIndex());
            result[SecondNode.getR()].setP(SecondNode.getIndex());
        }
        Node newNode(0, FirstNode.getW() + SecondNode.getW(), FirstNode.getIndex(), SecondNode.getIndex());
        q.push(newNode);
        if (q.size() == 1) {
            result[++idx] = q.top();
            result[idx].setIndex(idx);
            result[result[idx].getL()].setP(result[idx].getIndex());
            result[result[idx].getR()].setP(result[idx].getIndex());
            return {result, idx};
        }
    }
}

map<char, pair<char *, int>> static HuffmanCode(PNI args) {
    double all = 69640;
    double avglen = 0;
    map<char, pair<char *, int>> MII;
    Node *tree = args.first;
    int size = args.second;
    tree[size].code[0] = '\0';
    for (int i = size - 1; i > 0; i--) {
        strcpy(tree[i].code, tree[tree[i].getP()].code);
        if (tree[tree[i].getP()].getL() == i) {
            strcat(tree[i].code, "0");
        } else {
            strcat(tree[i].code, "1");
        }
        tree[i].setCode_len(strlen(tree[i].code));
        if (tree[i].getL() == 0 && tree[i].getR() == 0) {
            MII.insert({tree[i].getVal(), {tree[i].code, tree[i].getCode_len()}});
            avglen += (double)tree[i].getCode_len() * (tree[i].getW() / all);
        }
    }
    cout << avglen << endl;
    return MII;
}

map<char *, char> static CodeTurnover(map<char, pair<char *, int>> MCC) {
    map<char *, char> mcc;
    auto it = MCC.begin();
    while (it != MCC.end()) {
        mcc.insert({it->second.first, it->first});
        it++;
    }
    return mcc;
}

pair<char *, int> static Encode(char Buffer[], int length, map<char, pair<char *, int>> MCC) {
    string res;
    for (int i = 0; i < length; i++) {
        res += MCC[Buffer[i]].first;
    }
    cout << length * 8 << " " << res.length() << endl;
    int remainder = res.length() % 8;
    int cnt = (res.length() + ((remainder == 0)?0:(8 - remainder))) / 8;
    char *result = new char[cnt];
    for (int i = 1; i <= 8 - remainder; i++)
        res += "0";
    for (int i = 0; i < cnt; i++) {
        result[i] = stoi(res.substr(i * 8, 8), 0, 2);
    }
    return {result, cnt};
}

inline string change(char c) {
    string data;
    for (int i = 0; i < 8; i++) {
        //  data+=c&(0x01<<i);
        if ((c >> (i - 1)) & 0x01 == 1) {
            data += "1";
        } else {
            data += "0";
        }
    }
    for (int a = 1; a < 5; a++) {
        char x = data[a];
        data[a] = data[8 - a];
        data[8 - a] = x;
    }
    return data;
}

string static Decode (char Buffer[], int length, map<char*, char> MCC) {
    string data;
    for (int i = 0; i < length; i++) {
        data += change(Buffer[i]);
    }
    return data;
}

#endif