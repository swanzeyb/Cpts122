
#include "Row.h"

Row::Row(Table& table, int rowIndex): table_(table), rowIndex_(rowIndex) {}
Row::~Row() {}

Cell& Row::operator[](const string& colName) {
    if (rowIndex_ == table_.rowSize()) {
        table_.rowSize_ += 1;
    }
    return table_[colName][rowIndex_];
}

Cell& Row::operator[](const int& colIndex) const {
    return table_[table_.colNames()[colIndex]][rowIndex_];
}

Cell& Row::where(const string& value) const {
    for (const string& colName: table_.colNames()) {
        Cell& cell = table_[colName][rowIndex_];
        if (cell.value() == value) {
            return cell;
        }
    }
    throw invalid_argument("invalid argument: " + value);
}

void Row::setNAValue(const string& value) {
    for (const string& colName: table_.colNames()) {
        table_[colName][rowIndex_].setNAValue(value);
    }
}
