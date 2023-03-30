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

void BST::insert(BSTNode* node, char character, string morseCode)
{
	if (this->root == nullptr) // base case
	{
		// we know the tree is empty
		this->root = new BSTNode(character, morseCode); // mpLeft, mpRight are nullptr
	}
	else if (character > node->getCharacter())
	{
		// pTree contains the address of the current node that we're visiting
		// is the right subtree of the node that we're visiting empty?
		if (node->getRightPtr() == nullptr)
		{
			node->setRightPtr(new BSTNode(character, morseCode));
		}
		else // the right subtree is not empty
		{
			insert(node->getRightPtr(), character, morseCode);
		}
	}
	else if (character < node->getCharacter())
	{
		// is the left subtree empty?
		if (node->getLeftPtr() == nullptr)
		{
			node->setLeftPtr(new BSTNode(character, morseCode));
		}
		else // the left subtree is not empty
		{
			insert(node->getLeftPtr(), character, morseCode);
		}
	}
	else
	{
		cout << "duplicate: " << character << endl;
	}
}

void BST::print()
{
    print(this->root);
}

void BST::print(BSTNode* node)
{
	if (node != nullptr)
	{
		print(node->getLeftPtr()); // go left
		cout << node->getCharacter() << " " << node->getMorseCode() << endl; // process data
		print(node->getRightPtr()); // go right
	}
}
