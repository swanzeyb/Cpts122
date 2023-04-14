
#include "TransactionNode.h"

TransactionNode::TransactionNode(const string &type, int units): Node(units), mType_(type) {}

TransactionNode::TransactionNode(const TransactionNode& other): Node(other.mData_), mType_(other.mType_) {}

TransactionNode::~TransactionNode() {}

string TransactionNode::getType() const {
    return mType_;
}

void TransactionNode::setType(const string& type) {
    mType_ = type;
}

void TransactionNode::printData() const {
    cout << mData_ << " " << mType_ << endl;
}
