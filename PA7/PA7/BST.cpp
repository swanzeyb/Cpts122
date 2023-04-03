/**
 * @file BST.h
 * @brief Implements a binary search tree that loads in the morse code table
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include "BST.h"

BST::BST() {
    fstream file;
    file.open("MorseTable.txt");

    while (!file.eof()) {
        char character;
        string morseCode;
        file >> character >> morseCode;
        insert(root, character, morseCode);
    }

    file.close();
}

void BST::insert(BSTNode* node, char character, string morseCode) {
	if (this->root == nullptr) {
		this->root = new BSTNode(character, morseCode);
	} else if (character > node->getCharacter()) {
		if (node->getRightPtr() == nullptr) {
			node->setRightPtr(new BSTNode(character, morseCode));
		} else {
			insert(node->getRightPtr(), character, morseCode);
		}
	} else if (character < node->getCharacter()) {
		if (node->getLeftPtr() == nullptr) {
			node->setLeftPtr(new BSTNode(character, morseCode));
		} else {
			insert(node->getLeftPtr(), character, morseCode);
		}
	} else {
        // Duplicate
    }
}

void BST::print() {
    print(this->root);
}

void BST::print(BSTNode* node) {
	if (node != nullptr) {
		print(node->getLeftPtr());
		cout << node->getCharacter() << " " << node->getMorseCode() << endl;
		print(node->getRightPtr());
	}
}

string BST::search(char character) {
    return search(this->root, character);
}

string BST::search(BSTNode* node, char character) {
    if (node == nullptr) {
        return "";
    } else if (character > node->getCharacter()) {
        return search(node->getRightPtr(), character);
    } else if (character < node->getCharacter()) {
        return search(node->getLeftPtr(), character);
    } else {
        return node->getMorseCode();
    }
}
