
#include "Node.h"

Node::Node(const int data): mData_(data), mpLeft_(nullptr), mpRight_(nullptr) {}
Node::~Node() {}

int Node::getData() const {
    return mData_;
}

void Node::setData(const int data) {
    mData_ = data;
}

Node*& Node::getLeft() {
    return mpLeft_;
}

void Node::setLeft(Node *pLeft) {
    mpLeft_ = pLeft;
}

Node*& Node::getRight() {
    return mpRight_;
}

void Node::setRight(Node *pRight) {
    mpRight_ = pRight;
}
