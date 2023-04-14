/**
 * @file TransactionalNode.cpp
 * @brief Transactional Node stores transaction data.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"

using std::string;
using std::cout;
using std::endl;

class TransactionNode : public Node {
public:
    TransactionNode(const string &type, int units);
    TransactionNode(const TransactionNode& other);
    ~TransactionNode();

    /**
     * @brief Get the name of the product.
     * 
     * @return string 
     */
    string getType() const;

    /**
     * @brief Set the name of the product.
     * 
     * @param type 
     */
    void setType(const string& type);

    /**
     * @brief Print the data in the node.
     * 
     */
    void printData() const override;

private:
    string mType_;
};
