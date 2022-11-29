//
// Created by TBK on 2022/11/24.
//

#ifndef __DATAPROCESS_CPP__
#define __DATAPROCESS_CPP__

#include <map>
#include <iostream>
#include <fstream>
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
        // 非叶子节点
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
//    double all = 69640;
//    double avglen = 0;
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
//            avglen += (double)tree[i].getCode_len() * (tree[i].getW() / all);
        }
    }
//    cout << avglen << endl;
    return MII;
}

pair<char *, int> static Encode(char Buffer[], int length, map<char, pair<char *, int>> MCC) {
    string res;
    for (int i = 0; i < length; i++) {
        res += MCC[Buffer[i]].first;
    }
    int remainder = res.length() % 8;
    int cnt = (res.length() + ((remainder == 0) ? 0 : (8 - remainder))) / 8;
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


map<string, char> static CodeTurnover(map<char, pair<char *, int>> MCC) {
    map<string, char> mcc;
    auto it = MCC.begin();
    while (it != MCC.end()) {
        cout << (int) it->first << " ";
        for (int i = 0; i < it->second.second; i++)
            cout << it->second.first[i + 1];
        cout << endl;
        it++;
    }
    getchar();
    while (it != MCC.end()) {
        mcc.insert({it->second.first, it->first});
        it++;
    }
    return mcc;
}

string static Decode(char *Buffer, int length, map<string, char> MCC) {
    string data;
    for (int i = 0; i < length; i++) {
        data += change(Buffer[i]);
    }
    string tmp, DataOrigin;
    for (int i = 0; i < data.length(); i++) {
        tmp += data[i];
        if (MCC.count(tmp)) {
            DataOrigin += MCC[tmp];
            tmp = "";
        }
    }
    return DataOrigin;
}

void static storeTree(map<char, pair<char *, int>> result, string path) {
    fstream fout(path, ios::binary | ios::out);
    fout.seekg(0, ios::beg);
    auto it = result.begin();
    while (it != result.end()) {
        fout.write((char *) &it->first, sizeof(char));
        fout.write((char *) &it->second.second, sizeof(int));
        for (int i = 0; i < it->second.second; i++)
            fout.write((char *) &it->second.first[i], sizeof(char));
        it++;
    }
    fout.close();
}

map<char, pair<char *, int>> static attainTree(string path) {
    map<char, pair<char *, int>> tmp;
    fstream fin(path, ios::binary | ios::in);
    fin.seekg(0, ios::beg);
    char a;
    int c;
    while (!fin.eof()) {
        fin.read((char *) &a, sizeof(char));
        fin.read((char *) &c, sizeof(int));
        char *b = new char[c];
        for (int i = 0; i < c; i++) {
            fin.read((char *) &b[i], sizeof(char));
        }
        tmp.insert({a, {b, c}});
    }
    fin.close();

    map<char, pair<char *, int>> result;
    auto it = tmp.begin();
    while (it != tmp.end()) {
        int a = it->second.second;
        char *temp = new char[a + 1];
        temp[a] = '\0';
        for (int i = 0; i < a; i++) {
            temp[i] = it->second.first[i];
        }
        result.insert({it->first, {temp, it->second.second}});
        it++;
    }
    return result;
}


#endif