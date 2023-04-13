
#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Cell.h"
#include "Col.h"
#include "Row.h"
#include "../LinkedList.h"

using std::string;
using std::to_string;
using std::fstream;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::invalid_argument;
using std::find;

template <typename T>
class Converter;

class Row;

class Table {
public:
    Table();
    ~Table();

    friend Row;
    friend Col;
    
    Col operator[](const string& colName);
    Row operator[](const int& rowIndex);
    // Iterator for each row in the table
    class Iterator;

    Iterator begin();

    Iterator end();

    int rowSize() const;

    int colSize() const;

    vector<string>& colNames();

    bool exists(const string& key);

    bool exists(const int& key);

    void addColumn(const string& name);

    void addValue(const string& column, string& value);

    Table* select(const vector<string>& colNames);

    void readCSV(const string& filePath, const char delimiter = ',', const char escape = '"');

    void writeCSV(const string& filePath, const char delimiter = ',', const char escape = '"') const;
    
    template <typename T>
    Converter<T> convert() {
        return Converter<T>(*this);
    }

    template <typename K, typename V>
    Cell& where(const K& key, const V& value) {
        return (*this)[key].where(to_string(value));
    }

    template <typename K, typename V>
    bool exists(const K& key, const V& value) {
        try {
            Cell& cell = (*this)[key].where(to_string(value));
            return true;
        } catch(const std::exception& e) {
            return false;
        }
    }

private:
    unordered_map< string, vector<Cell> > cols_;
    vector<string> colNames_;
    int colSize_;
    int rowSize_;
};

template <typename T>
class Converter {
public:
    Converter(Table& table): table_(table), records_() {
        for (size_t r = 0; r < table.rowSize(); r++) {
            records_.push_back(T());
        }
    }
    ~Converter() {}
    
    template<typename U>
    Converter<T>& bindColumn(const string& colName, void (T::*setter)(U)) {
        for (size_t rowIndex = 0; rowIndex < records_.size(); ++rowIndex) {
            const Cell& cell = table_[colName][rowIndex];
            (records_[rowIndex].*setter)(cell.value<U>());
        }
        return *this;
    }

    Converter<T>& toLinkedList(LinkedList<T>& list) {
        for (const T& record: records_) {
            list.insertAtFront(record);
        }
        return *this;
    }

private:
    Table& table_;
    vector<T> records_;
};
