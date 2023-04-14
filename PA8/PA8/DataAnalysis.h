
#pragma once

#include <iostream>
#include "BST.h"
#include "TransactionNode.h"

using std::cout;
using std::endl;

class DataAnalysis {
public:
    static void displayTrees(BST<TransactionNode> bought, BST<TransactionNode> sold);
    static void displayTrends(BST<TransactionNode> bought, BST<TransactionNode> sold);
};
