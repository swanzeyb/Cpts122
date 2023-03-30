/**
 * @file BSTNode.h
 * @brief The binary search tree node that holds the data for the morse code table
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#pragma once

#include <string>
using std::string;

class BSTNode {
public:
    BSTNode(char character, string morseCode) : character(character), morseCode(morseCode), left(nullptr), right(nullptr) {}
    BSTNode(const BSTNode &other) : character(other.character), morseCode(other.morseCode), left(other.left), right(other.right) {}
    ~BSTNode() {
        delete left;
        delete right;
    }
    BSTNode* getLeftPtr();
    BSTNode* getRightPtr();
    void setLeftPtr(BSTNode* left);
    void setRightPtr(BSTNode* right);
    char getCharacter();
    string getMorseCode();
private:
    char character;
    string morseCode;
    BSTNode *left;
    BSTNode *right;
};
