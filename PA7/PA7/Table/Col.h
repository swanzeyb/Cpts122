
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

    Cell& operator[](const int& rowIndex) const;
    Cell& where(const string& value) const;

private:
    vector<Cell>& col_;
    const string& header_;
};
