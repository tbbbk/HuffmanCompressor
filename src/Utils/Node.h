//
// Created by TBK on 2022/11/23.
//

#pragma once


class Node {
private:
    char val;
    int w;
    int index, l = 0, r = 0, p = 0, code_len = 0;
public:
    char code[255];
    Node();

    Node(int val, int w);

    Node(int val, int w, int l, int r);

    void setCode_len(int code_len);

    int getCode_len();

    char getVal();

    void setVal(char val);

    int getW();

    void setP(int p);

    void setW(int w);

    void setL(int l);

    void setR(int r);

    void setIndex(int index);

    int getL();

    int getR();

    int getIndex();

    int getP();

    bool operator<(const Node &x) const;
};


