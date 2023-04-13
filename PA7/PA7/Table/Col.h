
#pragma once

#include <string>
#include <vector>
#include "Cell.h"

using std::string;
using std::vector;
using std::invalid_argument;

class Col {
public:
    Col(vector<Cell>& col, const string& header);
    ~Col();

    /**
     * @brief Overload the [] operator to access a cell
     * 
     * @param rowIndex 
     * @return Cell& 
     */
    Cell& operator[](const int& rowIndex) const;

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
    vector<Cell>& col_;
    const string& header_;
};
