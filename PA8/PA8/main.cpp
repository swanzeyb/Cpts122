/**
 * @file Main.cpp
 * @brief Create a program to track student attendance using LinkedLists.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#include <iostream>
#include <string>
#include "Menu.h"
#include "Table/Table.h"
#include "BST.h"
#include "TransactionNode.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char *const argv[])
{
    // Load the sales data
    Table table;
    table.readCSV("data.csv");

    // Split the data into two BSTs
    BST<TransactionNode> bought;
    BST<TransactionNode> sold;

    for (int i = 0; i < table.rowSize(); i++) {
        Row row = table[i];
        const string& type = row["Type"].value();
        const int& units = row["Units"].value<int>();

        cout << row["Units"].value() << endl;
        cout << row["Type"].value() << endl;
        bought.insert(TransactionNode(type, units));

        // if (row["Transaction"].value() == "Purchased") {
        //     bought.insert(TransactionNode(type, units));
        // } else {
        //     sold.insert(TransactionNode(type, units));
        // }
        
        // Units,Type,Transaction
        // cout << row["Units"].value() << endl;
        // cout << row["Type"].value() << endl;
        // cout << row["Transaction"].value() << endl;
    }

    Menu::clearScreen();
    bought.inOrderTraversal();

    return 0;
}
