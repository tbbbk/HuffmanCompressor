//
// Created by TBK on 2022/11/24.
//

#ifndef HUFFMAN_COMPRESSOR_FILEOPERATION_H
#define HUFFMAN_COMPRESSOR_FILEOPERATION_H

#include <iostream>
#include <fstream>

using namespace std;

class FileOperation {
private:
    char *Buffer;
    fstream f;
    int length;
    string path;
public:
    ~FileOperation();

    void setPath(string Path);

    void BinaryRead();

    void BinaryWrite();

    char *getBuffer();

    void setBuffer(char Buffer[], int length);

    int Length() const;
};

#endif //HUFFMAN_COMPRESSOR_FILEOPERATION_H
