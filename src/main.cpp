//This program uses to write and read functions.
#include <iostream>
#include <queue>
#include "Utils/FileOperation.h"
#include "Utils/DataProcess.cpp"

using namespace std;
typedef pair<Node *, int> PNI;

int main() {
    // 数据操作类
    FileOperation tbk;
    tbk.setPath("../src/Data/test.dat");
    tbk.BinaryRead();
    //**********************************************************************
    map<char, pair<char*, int>> weight = attainTree("../src/Data/test.tree");
    string data = Decode(tbk.getBuffer(), tbk.Length(), CodeTurnover(weight));
    tbk.setPath("../src/test.jpg");
    tbk.setBuffer(const_cast<char *>(data.c_str()), data.length());
    tbk.BinaryWrite();
    //**********************************************************************
//    auto q = CountData(tbk.getBuffer(), tbk.Length());
//    PNI res = CreateHuffmanTree(q);
    // result 需要储存的哈夫曼编码结果
//    map<char, pair<char *, int>> result = HuffmanCode(res);
//    storeTree(result, "../src/Data/test.tree");
    // 编码结果
//    pair<char *, int> finalResult = Encode(tbk.getBuffer(), tbk.Length(), result);
//    tbk.setPath("../src/Data/test.dat");
//    tbk.setBuffer(finalResult.first, finalResult.second);
//    tbk.BinaryWrite();
    //**********************************************************************
//
//    auto it = result.begin();
//    cout << result.size() << endl;
//    while (it != result.end()) {
//        cout << (int)it->first << ":" << it->second.first << ":" << it->second.second << endl;
//        it++;
//    }


//    cout << weight.size() << endl;
//    auto itt = weight.begin();
//    while (itt != weight.end()) {
//        cout << (int)itt->first << ":" << itt->second.first << ":" << itt->second.second<< endl;
//        itt++;
//    }
}