//This program uses to write and read functions.
#include <iostream>
#include <queue>
#include "Utils/FileOperation.h"
#include "Utils/DataProcess.cpp"

using namespace std;
typedef pair<Node *, int> PNI;

int main() {
    //*********************************************************
    FileOperation tbk;
    tbk.setPath("../src/img/shit.jpg");
    tbk.BinaryRead();
    auto q = CountData(tbk.getBuffer(), tbk.Length());
    PNI res = CreateHuffmanTree(q);
    map<char, pair<char *, int>> result = HuffmanCode(res);
    pair<char *, int> finalResult = Encode(tbk.getBuffer(), tbk.Length(), result);
    string tmp = Decode(finalResult.first, finalResult.second, CodeTurnover(result));
//    //*********************************************************
    char *a = finalResult.first;
    int len = finalResult.second;
    tbk.setPath("../src/data/avatar.dat");
    tbk.setBuffer(a, len);
    tbk.BinaryWrite();




//    cout << finalResult;
//    string a = "11";
//    int b = stoi(a, 0, 2);
//    cout << b;
//    FileOperation a;
//    a.setPath("../src/data/avatar.dat");
//    a.BinaryRead();
//    char* Buffer = a.getBuffer();
//    for (int i = 0; i < a.Length(); i++) {
//        cout << Buffer[i];
//    }
//    cout << endl << a.Length();

//    cout << tbk.Length();
//    getchar();
//    priority_queue<Node> q;
//    Node a(1, 5);
//    q.push(a);
//    Node b(2, 15);
//    q.push(b);
//    Node c(3, 40);
//    q.push(c);
//    Node d(4, 30);
//    q.push(d);
//    Node e(5, 10);
//    q.push(e);
//    PNI res = CreateHuffmanTree(q);
//    map<char, pair<char *, int>> result = HuffmanCode(res);

//    cout << finalResult << endl;
//    char a[finalResult.length() + 1];
//    strcpy(a, finalResult.c_str());

    auto it = result.begin();
    while (it != result.end()) {
        cout << (int) it->first << ":";
        for (int i = 0; i < it->second.second; i++)
            cout << it->second.first[i];
        cout << endl;
        it++;
    }

//    unsigned char a =-1;
//    cout << a;


//    Node *shit = res.first;
//    for (int i = 1; i <= res.second; i++) {
//        cout << i << "th: " << int(shit[i].getVal()) << ":" << shit[i].getW() << " l:" << shit[i].getL() << " r:"
//             << shit[i].getR() << " p:" << shit[i].getP() << endl;
//    }
//    int sum = 0;
//    while (!q.empty()) {
//        auto t = q.top();
//        q.pop();
//        cout << (int)t.getVal() << ":" << t.getW() << endl;
//        sum += t.getW();
//    }
//    cout << sum;


//    map<int, int>::iterator it = b.begin();
//    int sum = 0;
//    while (it != b.end()) {
//        cout << it->first << ' ' << it->second << endl;
//        sum += it->second;
//        it++;
//    }
//    cout << sum;

//    char a[999] = "ab";
//    string b = "a";
//    b += a;
//    cout << b;
}