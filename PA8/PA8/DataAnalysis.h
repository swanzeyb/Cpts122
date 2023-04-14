/**
 * @file DataAnalysis.cpp
 * @brief Static class to work with the BST data.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <iostream>
#include "BST.h"
#include "TransactionNode.h"

using std::cout;
using std::endl;

class DataAnalysis {
public:
    /**
     * @brief Print the data in the trees.
     * 
     * @param bought 
     * @param sold 
     */
    static void displayTrees(BST<TransactionNode> bought, BST<TransactionNode> sold);

    /**
     * @brief Print the sales trends in the data.
     * 
     * @param bought 
     * @param sold 
     */
    static void displayTrends(BST<TransactionNode> bought, BST<TransactionNode> sold);
};
