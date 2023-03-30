
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
