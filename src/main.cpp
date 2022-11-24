//This program uses the write and read functions.
#include <iostream>
#include "Utils/FileOperation.h"
#include "Utils/DataProcess.cpp"

using namespace std;

int main() {
    FileOperation tbk;
    tbk.setPath("../src/data/avator.bat");
    tbk.BinaryRead();
    map<int, int> b = CountData(tbk.getBuffer(), tbk.Length());
//    Node* a = CreateHuffmanTree(b);



//    map<int, int>::iterator it = b.begin();
//    int sum = 0;
//    while (it != b.end()) {
//        cout << it->first << ' ' << it->second << endl;
//        sum += it->second;
//        it++;
//    }
//    cout << sum;
}