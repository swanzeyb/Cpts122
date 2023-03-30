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
    void insert(BSTNode* node, char character, string morseCode);
    void print();
    string search(char character);
private:
    void print(BSTNode* node);
    BSTNode *root;
};
