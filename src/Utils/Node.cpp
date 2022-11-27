//
// Created by TBK on 2022/11/24.
//
#ifndef __NODE_H__
#define __NODE_H__

#include "Node.h"

Node::Node() {
    // Nothing here :)
}

Node::Node(int val, int w) {
    this->val = val;
    this->w = w;
}

Node::Node(int val, int w, int l, int r) {
    this->val = val;
    this->w = w;
    this->l = l;
    this->r = r;
}

char Node::getVal() {
    return this->val;
}

void Node::setVal(char val) {
    this->val = val;
}

int Node::getW() {
    return this->w;
}

void Node::setW(int w) {
    this->w = w;
}

void Node::setL(int l) {
    this->l = l;
}

void Node::setR(int r) {
    this->r = r;
}

void Node::setIndex(int index) {
    this->index = index;
}

void Node::setP(int p) {
    this->p = p;
}

int Node::getL() {
    return this->l;
}

int Node::getR() {
    return this->r;
}

int Node::getIndex() {
    return this->index;
}

int Node::getP() {
    return this->p;
}

int Node::getCode_len() {
    return this->code_len;
}

void Node::setCode_len(int code_len) {
    this->code_len = code_len;
}

bool Node::operator<(const Node &x) const {
    if (this->w != x.w)
        return this->w > x.w;
    else
        return this->l + this->r < x.l + x.r;
}

#endif