
#pragma once

#include <string>

using std::string;

class Node {
public:
    Node(const int data);
    virtual ~Node();

    int getData() const;
    void setData(const int data);
    
    Node*& getLeft();
    void setLeft(Node *pLeft);

    Node*& getRight();
    void setRight(Node *pRight);

    // Pure virtual function
    virtual void printData() const = 0;

protected:
    int mData_;
    Node *mpLeft_;
    Node *mpRight_;
};
