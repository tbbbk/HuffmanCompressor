//This program uses the write and read functions.
#include <iostream>
#include "Utils/FileOperation.h"
using namespace std;

int main() {
    string path = "../src/img/test.bat";
    FileOperation tbk;
    tbk.setPath(path);
    tbk.BinaryRead();
    path = "../src/img/test.jpg";
    tbk.setPath(path);
    tbk.BinaryWrite();
}