
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

    string getType() const;
    void setType(const string& type);

    void printData() const override;

private:
    string mType_;
};
