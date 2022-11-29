//This program uses to write and read functions.
#include <iostream>
#include <queue>
#include "Utils/FileOperation.h"
#include "Utils/DataProcess.cpp"

using namespace std;
typedef pair<Node *, int> PNI;

int main() {
//    // 数据操作类
//    FileOperation tbk;
//    tbk.setPath("../src/Data/tbk.txt");
//    tbk.BinaryRead();
//    auto q = CountData(tbk.getBuffer(), tbk.Length());
//    PNI res = CreateHuffmanTree(q);
//    // result 需要储存的哈夫曼编码结果
//    map<char, pair<char *, int>> result = HuffmanCode(res);
//    storeTree(result, "../src/Data/tbk.tree");
//    // 编码结果
//    pair<char *, int> finalResult = Encode(tbk.getBuffer(), tbk.Length(), result);
//    // 译码结果
//
//    auto it = result.begin();
//    while (it != result.end()) {
//        cout << (int)it->first << ":" << it->second.first << endl;
//        it++;
//    }


    map<char, pair<char*, int>> tmp = attainTree("../src/Data/tbk.tree");
    cout << tmp.size() << endl;
    auto itt = tmp.begin();
    while (itt != tmp.end()) {
        cout << (int)itt->first << ":" << itt->second.first << endl;
        itt++;
    }
}