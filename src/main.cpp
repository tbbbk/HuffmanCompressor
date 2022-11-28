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
    tbk.setPath("../src/img/avatar.jpg");
    tbk.BinaryRead();
    auto q = CountData(tbk.getBuffer(), tbk.Length());
    PNI res = CreateHuffmanTree(q);
    // result 需要储存的哈夫曼编码结果
    map<char, pair<char *, int>> result = HuffmanCode(res);
    // 编码结果
    pair<char *, int> finalResult = Encode(tbk.getBuffer(), tbk.Length(), result);
    // 译码结果
    string OriginData = Decode(finalResult.first, finalResult.second, CodeTurnover(result));
    // 压缩储存
    tbk.setPath("../src/data/avatar.dat");
    tbk.setBuffer(finalResult.first, finalResult.second);
    tbk.BinaryWrite();
}