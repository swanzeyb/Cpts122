
#include "Cell.h"

Cell::Cell(int row): value_(""), row_(row) {}
Cell::Cell(const string& value, int row): value_(value), row_(row) {}
Cell::Cell(string& value, int row): value_(value), row_(row) {}
Cell::~Cell() {}

void Cell::operator=(const string& value) {
    value_ = value;
}

string Cell::value() const {
    return value_;
}

string& Cell::value() {
    return value_;
}

void Cell::value(const string& value) {
    value_ = value;
}

int& Cell::getRow() {
    return row_;
}

void Cell::setRow(const int& row) {
    row_ = row;
}

void Cell::setNAValue(const string& value) {
    if (value_ == "") {
        value_ = value;
    }
}
