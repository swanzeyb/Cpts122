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
#include "DataAnalysis.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char *const argv[])
{
    Menu::clearScreen();

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

        if (row["Transaction"].value() == "Purchased") {
            bought.insert(TransactionNode(type, units));
        } else {
            sold.insert(TransactionNode(type, units));
        }
    }

    // Display the data
    cout << "Sales Figures:" << endl;
    DataAnalysis::displayTrees(bought, sold);
    cout << endl << endl;

    // Display trends
    cout << "Sales Trends:" << endl;
    DataAnalysis::displayTrends(bought, sold);

    Menu::waitForEnter();
    return 0;
}
