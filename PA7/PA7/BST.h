/**
 * @file BST.h
 * @brief Implements a binary search tree that loads in the morse code table
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "BSTNode.h"
using std::string;
using std::fstream;
using std::cout;
using std::endl;

class BST {
public:
    BST();
    BST(const BST &other) : root(other.root) {}
    ~BST() {
        delete root;
    }
    void insert(BSTNode* node, char character, string morseCode);
    string search(char character);
    void print();
private:
    string search(BSTNode* node, char character);
    void print(BSTNode* node);
    BSTNode *root;
};
