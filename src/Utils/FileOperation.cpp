//
// Created by TBK on 2022/11/24.
//
#include "FileOperation.h"
#include <iostream>
using namespace std;

void FileOperation::setPath(string path) {
    this->path = path;
    return;
}

void FileOperation::BinaryRead() {
    this->f.open(this->path, ios::in | ios::binary);
    if (!this->f) {
        cout << "文件打开失败" << endl;
        return;
    }
    this->f.seekg(0, ios::end);
    this->length = f.tellg();
    cout << "文件字节数：" << length << endl;
    this->f.seekg(0, ios::beg);
    this->Buffer = new char[length];
    this->f.read(Buffer, length * sizeof(char));
    this->f.close();
}

void FileOperation::BinaryWrite() {
    this->f.open(this->path, ios::out | ios::binary);
    if (!f) {
        cout << "文件打开失败" << endl;
        return;
    }
    f.write(this->Buffer, this->length * sizeof(char));
    f.close();
    return;
}

char* FileOperation::getBuffer() {
    return this->Buffer;
}