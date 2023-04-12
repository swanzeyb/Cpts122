
#include "Row.h"

Row::Row(Table& table, int rowIndex): table_(table), rowIndex_(rowIndex) {}
Row::~Row() {}

Cell& Row::operator[](const string& colName) {
    if (!table_.exists(colName)) {
        Cell& cell = table_[colName][rowIndex_];
        push_back(&cell);
    }
    return *(vector<Cell*>::operator[](getColIndex(colName)));
}

Cell& Row::operator[](const int& colIndex) const {
    return *(vector<Cell*>::operator[](colIndex));
}

Cell& Row::where(const string& value) const {
    for (Cell* cell: *this) {
        if (cell->value() == value) {
            return *cell;
        }
    }
    throw invalid_argument("invalid argument: " + value);
}

int Row::getColIndex(const string& colName) const {
    vector<string>& colNames_ = table_.colNames();
    auto it = find(colNames_.begin(), colNames_.end(), colName);
    if (it == colNames_.end()) {
        return colNames_.size();
    }
    return it - colNames_.begin();
}
