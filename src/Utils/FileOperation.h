//
// Created by TBK on 2022/11/24.
//

#ifndef HUFFMAN_COMPRESSOR_FILEOPERATION_H
#define HUFFMAN_COMPRESSOR_FILEOPERATION_H
#include <fstream>
using namespace std;


class FileOperation {
private:
    char* Buffer;
    fstream f;
    long long length;
    string path;
public:
    void setPath(string path);
    void BinaryRead();
    void BinaryWrite();
    char* getBuffer();
};


#endif //HUFFMAN_COMPRESSOR_FILEOPERATION_H
