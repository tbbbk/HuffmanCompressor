//
// Created by TBK on 2022/11/23.
//

#pragma once


class Node {
private:
    char val;
    int w;
    int index, l = 0, r = 0, p = 0;
    char code[255];
public:
    Node();

    Node(int val);

    bool operator<(Node x);

    char getVal();
};


