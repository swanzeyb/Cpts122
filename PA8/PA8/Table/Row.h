
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

    /**
     * @brief Overload the [] operator to access a cell
     * 
     * @param colName 
     * @return Cell& 
     */
    Cell& operator[](const string& colName);

    /**
     * @brief Overload the [] operator to access a cell
     * 
     * @param colIndex 
     * @return Cell& 
     */
    Cell& operator[](const int& colIndex) const;

    /**
     * @brief Returns the cell matching the specified value
     * 
     * @param value 
     * @return Cell& 
     */
    Cell& where(const string& value) const;

    /**
     * @brief Sets what value to return if the cell is empty
     * 
     * @param value 
     */
    void setNAValue(const string& value);

private:
    Table& table_;
    int rowIndex_;
};
