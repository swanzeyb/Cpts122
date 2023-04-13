
#pragma once

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Cell {
public:
    Cell(int row);
    Cell(const string& value, int row);
    Cell(string& value, int row);
    ~Cell();

    void operator=(const string& value);

    template<typename T>
    T value() const {
        return Cell::parse<T>(value_);
    }

    string value() const;

    string& value();

    void value(const string& value);

    int& getRow();

    void setRow(const int& row);

    void setNAValue(const string& value);

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
