
#pragma once

#include <vector>
#include "Cell.h"
#include "Table.h"

using std::vector;
using std::invalid_argument;

class Table;

class Row {
public:
    Row(Table& table, int rowIndex);
    ~Row();

    Cell& operator[](const string& colName);

    Cell& operator[](const int& colIndex) const;

    Cell& where(const string& value) const;

    void setNAValue(const string& value);

private:
    Table& table_;
    int rowIndex_;
};
