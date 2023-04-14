
#include "DataAnalysis.h"

void DataAnalysis::displayTrees(BST<TransactionNode> bought, BST<TransactionNode> sold) {
    cout << "Purchased:" << endl;
    bought.inOrderTraversal();
    cout << "Sold:" << endl;
    sold.inOrderTraversal();
}

void DataAnalysis::displayTrends(BST<TransactionNode> bought, BST<TransactionNode> sold) {
    const TransactionNode& mostBought = bought.findLargest();
    const TransactionNode& leastBought = bought.findSmallest();
    const TransactionNode& mostSold = sold.findLargest();
    const TransactionNode& leastSold = sold.findSmallest();

    cout << "Most purchased:" << endl;
    cout << mostBought.getType() << ", " << mostBought.getData() << " Units" << endl;

    cout << "Least purchased:" << endl;
    cout << leastBought.getType() << ", " << leastBought.getData() << " Units" << endl;

    cout << "Most sold:" << endl;
    cout << mostSold.getType() << ", " << mostSold.getData() << " Units" << endl;

    cout << "Least sold:" << endl;
    cout << leastSold.getType() << ", " << leastSold.getData() << " Units" << endl;
}
