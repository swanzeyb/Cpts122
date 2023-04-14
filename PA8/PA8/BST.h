
#pragma once

#include <string>
#include "Node.h"

using std::string;

template <typename T>
class BST {
public:
    BST(): mpRoot_(nullptr) {}
    ~BST() {}

    Node* getRoot() const {
        return mpRoot_;
    }

    void setRoot(Node* pRoot) {
        mpRoot_ = pRoot;
    }

    template <typename U>
    void insert(const U& data) {
        if (mpRoot_ == nullptr) {
            mpRoot_ = new U(data);
        } else {
            this->insert(mpRoot_, data);
        }
    }

    void inOrderTraversal() const {
        this->inOrderTraversal(mpRoot_);
    }

    T& findSmallest() const {
        return this->findSmallest(mpRoot_);
    }

    T& findLargest() const {
        return this->findLargest(mpRoot_);
    }

private:
    Node *mpRoot_;

    void destroyTree(Node* pNode) {
        if (pNode != nullptr) {
            destroyTree(pNode->getLeft());
            destroyTree(pNode->getRight());
            delete pNode;
        }
    }

    template <typename U>
    Node* insert(Node* pNode, const U& data) {
        if (pNode == nullptr) {
            pNode = new U(data);
        } else if (data.getData() < pNode->getData()) {
            pNode->setLeft(insert(pNode->getLeft(), data));
        } else if (data.getData() > pNode->getData()) {
            pNode->setRight(insert(pNode->getRight(), data));
        }
        return pNode;
    }

    void inOrderTraversal(Node* pNode) const {
        if (pNode != nullptr) {
            inOrderTraversal(pNode->getLeft());
            pNode->printData();
            inOrderTraversal(pNode->getRight());
        }
    }

    T& findSmallest(Node* pNode) const {
        if (pNode->getLeft() == nullptr) {
            return pNode->getData();
        } else {
            return findSmallest(pNode->getLeft());
        }
    }

    T& findLargest(Node* pNode) const {
        if (pNode->getRight() == nullptr) {
            return pNode->getData();
        } else {
            return findLargest(pNode->getRight());
        }
    }
};
