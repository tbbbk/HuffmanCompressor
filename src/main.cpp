//This program uses to write and read functions.
#include <iostream>
#include <queue>
#include "Utils/FileOperation.h"
#include "Utils/DataProcess.cpp"

using namespace std;
typedef pair<Node *, int> PNI;

int main() {
    // ���ݲ�����
    FileOperation tbk;
    tbk.setPath("../src/img/avatar.jpg");
    tbk.BinaryRead();
    auto q = CountData(tbk.getBuffer(), tbk.Length());
    PNI res = CreateHuffmanTree(q);
    // result ��Ҫ����Ĺ�����������
    map<char, pair<char *, int>> result = HuffmanCode(res);
    // ������
    pair<char *, int> finalResult = Encode(tbk.getBuffer(), tbk.Length(), result);
    // ������
    string OriginData = Decode(finalResult.first, finalResult.second, CodeTurnover(result));
    // ѹ������
    tbk.setPath("../src/data/avatar.dat");
    tbk.setBuffer(finalResult.first, finalResult.second);
    tbk.BinaryWrite();
}