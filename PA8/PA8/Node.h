/**
 * @file Main.cpp
 * @brief An abstract class to represent a node in a tree.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <string>

using std::string;

class Node {
public:
    Node(const int data);
    virtual ~Node();

    /**
     * @brief Get the int data.
     * This acts like the key in the BST.
     * @return int 
     */
    int getData() const;

    /**
     * @brief Set the data int.
     * This acts like the key in the BST.
     * @param data 
     */
    void setData(const int data);
    
    /**
     * @brief Get the left tree node.
     * 
     * @return Node*& 
     */
    Node*& getLeft();

    /**
     * @brief Set the left tree node.
     * 
     * @param pLeft 
     */
    void setLeft(Node *pLeft);

    /**
     * @brief Get the right tree node.
     * 
     * @return Node*& 
     */
    Node*& getRight();

    /**
     * @brief Set the right tree node.
     * 
     * @param pRight 
     */
    void setRight(Node *pRight);

    /**
     * @brief Pure virtual function to print the data.
     * 
     */
    virtual void printData() const = 0;

protected:
    int mData_;
    Node *mpLeft_;
    Node *mpRight_;
};
