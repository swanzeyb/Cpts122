/**
 * @file BSTNode.h
 * @brief The binary search tree node that holds the data for the morse code table
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include "BSTNode.h"

BSTNode* BSTNode::getLeftPtr() {
    return left;
}

BSTNode* BSTNode::getRightPtr() {
    return right;
}

void BSTNode::setLeftPtr(BSTNode* left) {
    this->left = left;
}

void BSTNode::setRightPtr(BSTNode* right) {
    this->right = right;
}

char BSTNode::getCharacter() {
    return character;
}

string BSTNode::getMorseCode() {
    return morseCode;
}
