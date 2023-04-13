
#include "Col.h"

Col::Col(vector<Cell>& col, const string& header): col_(col), header_(header) {}
Col::~Col() {}

Cell& Col::operator[](const int& rowIndex) const {
    for (int r = col_.size(); r <= rowIndex; r++) {
        col_.push_back(Cell(r));
    }
    return col_[rowIndex];
}

Cell& Col::where(const string& value) const {
    for (Cell& cell: col_) {
        if (cell.value() == value) {
            return cell;
        }
    }
    throw invalid_argument("invalid argument: " + value);
}

void Col::setNAValue(const string& value) {
    for (Cell& cell: col_) {
        cell.setNAValue(value);
    }
}
