/**
 * @file Stack.h
 * @brief An implemntation of a Table structure
 * 
 * This class took inspiration from Python Dataframes.
 * It was designed to work kind of like a spreadsheet.
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

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
    
    /**
     * @brief Overload the [] operator to access a column
     * 
     * @param colName 
     * @return Col 
     */
    Col operator[](const string& colName);

    /**
     * @brief Overload the [] operator to access a row
     * 
     * @param rowIndex 
     * @return Row 
     */
    Row operator[](const int& rowIndex);
    
    /**
     * @brief Implements the iterator to enable iteration of each row
     * 
     */
    class Iterator;

    /**
     * @brief Get the begin iterator
     * 
     * @return Iterator 
     */
    Iterator begin();

    /**
     * @brief Get the end iterator
     * 
     * @return Iterator 
     */
    Iterator end();

    /**
     * @brief Gets the count of rows
     * 
     * @return int 
     */
    int rowSize() const;

    /**
     * @brief Gets the count of columns
     * 
     * @return int 
     */
    int colSize() const;

    /**
     * @brief Gets the column names
     * 
     * @return vector<string>& 
     */
    vector<string>& colNames();

    /**
     * @brief Checks if a column exists
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool exists(const string& key);

    /**
     * @brief Checks if a row exists
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool exists(const int& key);

    /**
     * @brief Adds a column to the table
     * 
     * @param name 
     */
    void addColumn(const string& name);

    /**
     * @brief Adds a value to a column
     * 
     * @param column 
     * @param value 
     */
    void addValue(const string& column, string& value);

    /**
     * @brief Returns a new table with the specified columns
     * 
     * @param colNames 
     * @return Table* 
     */
    Table* select(const vector<string>& colNames);

    /**
     * @brief Parses a CSV file into the table
     * 
     * @param filePath 
     * @param delimiter 
     * @param escape 
     */
    void readCSV(const string& filePath, const char delimiter = ',', const char escape = '"');

    /**
     * @brief Writes the contents of the table to a CSV file
     * 
     * @param filePath 
     * @param delimiter 
     * @param escape 
     */
    void writeCSV(const string& filePath, const char delimiter = ',', const char escape = '"') const;
    
    /**
     * @brief Convert the table contents to a certain type
     * 
     * @tparam T The type each row will be converted to
     * @return Converter<T> 
     */
    template <typename T>
    Converter<T> convert() {
        return Converter<T>(*this);
    }

    /**
     * @brief Returns the first cell found that contains the specified value
     * This lets us search the table using any combo of index types.
     * So we could search the rows with table[rowIndex],
     * Or we could search the columns with table[colName].
     * 
     * @tparam K int or string for row or column
     * @tparam V Any type that can be converted to a string
     * @param key 
     * @param value 
     * @return Cell& 
     */
    template <typename K, typename V>
    Cell& where(const K& key, const V& value) {
        return (*this)[key].where(to_string(value));
    }

    /**
     * @brief Returns true if the table contains the specified value
     * This lets us search the table using any combo of index types.
     * So we could search the rows with table[rowIndex],
     * Or we could search the columns with table[colName].
     * 
     * @tparam K int or string for row or column
     * @tparam V Any type that can be converted to a string
     * @param key 
     * @param value 
     * @return true 
     * @return false 
     */
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
    
    /**
     * @brief Sets which setter on the type to be converted to will be used for each table column
     * 
     * @tparam U Type of value the setter will accept
     * @param colName 
     * @param setter 
     * @return Converter<T>& 
     */
    template<typename U>
    Converter<T>& bindColumn(const string& colName, void (T::*setter)(U)) {
        for (size_t rowIndex = 0; rowIndex < records_.size(); ++rowIndex) {
            const Cell& cell = table_[colName][rowIndex];
            (records_[rowIndex].*setter)(cell.value<U>());
        }
        return *this;
    }

    /**
     * @brief Returns all the converted records in a LinkedList
     * 
     * @param list 
     * @return Converter<T>& 
     */
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
