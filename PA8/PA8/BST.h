/**
 * @file BST.cpp
 * @brief Generic Binary Search Tree implementation.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <string>
#include "Node.h"

using std::string;

template <typename T>
class BST {
public:
    BST(): mpRoot_(nullptr) {}
    ~BST() {
        // destroyTree(mpRoot_);
    }

    /**
     * @brief Get the Root object
     * 
     * @return Node* 
     */
    Node* getRoot() const {
        return mpRoot_;
    }

    /**
     * @brief Set the Root object
     * 
     * @param pRoot 
     */
    void setRoot(Node* pRoot) {
        mpRoot_ = pRoot;
    }

    /**
     * @brief Insert a new node into the tree.
     * 
     * @tparam U Record type
     * @param data 
     */
    template <typename U>
    void insert(const U& data) {
        if (mpRoot_ == nullptr) {
            mpRoot_ = new U(data);
        } else {
            this->insert(mpRoot_, data);
        }
    }

    /**
     * @brief Print the tree in ascending order.
     * 
     */
    void inOrderTraversal() const {
        this->inOrderTraversal(mpRoot_);
    }

    /**
     * @brief Find the smallest node in the tree.
     * 
     * @return T& Record type
     */
    T& findSmallest() {
        return this->findSmallest(mpRoot_);
    }

    /**
     * @brief Find the largest node in the tree.
     * 
     * @return T& Record type
     */
    T& findLargest() {
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

    T& findSmallest(Node* pNode) {
        if (pNode->getLeft() == nullptr) {
            return *(T*)pNode;
        } else {
            return findSmallest(pNode->getLeft());
        }
    }

    T& findLargest(Node* pNode) {
        if (pNode->getRight() == nullptr) {
            return *(T*)pNode;
        } else {
            return findLargest(pNode->getRight());
        }
    }
};
