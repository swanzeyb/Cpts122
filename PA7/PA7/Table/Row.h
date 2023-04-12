
#pragma once

#include <vector>
#include "Cell.h"
#include "Table.h"

using std::vector;
using std::invalid_argument;

class Table;

class Row : public vector<Cell*> {
public:
    Row(Table& table, int rowIndex);
    ~Row();

    Cell& operator[](const string& colName);

    Cell& operator[](const int& colIndex) const;

    Cell& where(const string& value) const;

private:
    Table& table_;
    int rowIndex_;

    int getColIndex(const string& colName) const;
};
