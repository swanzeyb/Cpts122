
#pragma once

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Cell {
public:
    Cell(int row): value_(""), row_(row) {}
    Cell(string& value, int row): value_(value), row_(row) {}
    ~Cell() {}

    void operator=(const string& value) {
        value_ = value;
    }

    template<typename T>
    T value() const {
        return Cell::parse<T>(value_);
    }

    string value() const {
        return value_;
    }

    void value(const string& value) {
        value_ = value;
    }

    int& getRow() {
        return row_;
    }

    void setRow(const int& row) {
        row_ = row;
    }

private:
    string value_;
    int row_;

    template<typename T>
    static T parse(const string& str) {
        stringstream ss(str);
        T value;
        ss >> value;
        if (ss.fail() || !ss.eof()) {
            return T();
        }
        return value;
    }
};
