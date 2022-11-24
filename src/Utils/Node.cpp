//
// Created by TBK on 2022/11/24.
//
#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"

Node::Node(int val) {
    this->val = val;
}

bool Node::operator<(Node x) {
    return this->val < x.val;
}

char Node::getVal() {
    return this->val;
}

#endif