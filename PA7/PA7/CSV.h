
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::string;
using std::stringstream;
using std::to_string;
using std::fstream;
using std::vector;
using std::unordered_map;
using std::find;
using std::cout;
using std::endl;

class Cell {
public:
    Cell(): value_() {}
    Cell(const string& value): value_(value) {}

    ~Cell() {}

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

private:
    string value_;

    template<typename T>
    static T parse(const string& str) {
        std::stringstream ss(str);
        T value;
        ss >> value;
        if (ss.fail() || !ss.eof()) {
            throw std::invalid_argument("invalid argument: " + str);
        }
        return value;
    }
};

class Row : public vector<Cell> {
public:
    Row(vector<string>& colNames): colNames_(colNames) {}
    ~Row() {}

    const Cell& operator[](const string colName) const {
        auto it = find(colNames_.begin(), colNames_.end(), colName);
        if (it == colNames_.end()) {
            throw std::invalid_argument("invalid argument: " + colName);
        }
        return vector<Cell>::operator[](it - colNames_.begin());
    }

private:
    vector<string>& colNames_;
};

class Table {
public:
    Table(): cols_(), colNames_(), colSize_(0), rowSize_(0) {}
    ~Table() {}
    
    vector<Cell>& operator[](const string& colName) {
        return cols_[colName];
    }

    Row operator[](const int rowIndex) {
        Row row(colNames_);
        for (const string colName: colNames_) {
            row.push_back(cols_[colName][rowIndex]);
        }
        return row;
    }

    // Iterator for each row in the table
    class Iterator {
    public:
        Iterator(Table& table, int rowIndex): table_(table), rowIndex_(rowIndex) {}
        ~Iterator() {}

        Iterator& operator++() {
            rowIndex_++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        bool operator==(const Iterator& other) const {
            return rowIndex_ == other.rowIndex_;
        }

        bool operator!=(const Iterator& other) const {
            return rowIndex_ != other.rowIndex_;
        }

        Row operator*() {
            return table_[rowIndex_];
        }
    private:
        Table& table_;
        int rowIndex_;
    };

    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, rowSize_);
    }

    void readCSV(const string filePath, const char delimiter = ',', const char escape = '"') {
        fstream file;
        file.open(filePath);

        if (file.is_open()) {
            char c = '\0';
            string line;
            string value;
            int rowIndex = 0;
            int colIndex = 0;
            bool escapedCol = false;

            // Start reading the CSV rows
            while (getline(file, line)) {

                // Read each char and build col
                stringstream ss(line);
                while (ss.get(c)) {
                    if (c == escape) {
                        escapedCol = !escapedCol;
                    } else if ((c == delimiter || c == '\r' || c == '\n') && !escapedCol) {
                        // At the end of the column value

                        // Setup our columns
                        if (rowIndex == 0) {
                            if (value == "") {
                                string colName;

                                if (colIndex == 0) {
                                    colName = "index_";
                                } else {
                                    colName = "Col " + to_string(colIndex);
                                }

                                addColumn(colName);
                            } else {
                                addColumn(value);
                            }
                        } else {
                            // Save the read data
                            string colName = colNames_[colIndex];

                            if (escapedCol && cols_[colName].size() == rowIndex) {
                                // If we already inserted data for this escaped col, append
                                Cell& cell = cols_[colName][rowIndex - 1]; // Subtract 1 from rowIndex because header row
                                cell.value(cell.value() + " " + value);
                            } else {
                                addValue(colName, value);
                            }
                        }

                        value = "";
                        colIndex += 1;
                    } else {
                        value += c;
                    }
                }

                rowIndex += 1;
                colIndex = 0;
                escapedCol = false;
            }

            file.close();
        }
    }

    void writeCSV(const string filePath, const char delimiter = ',', const char escape = '"') {
        fstream file;
        file.open(filePath, std::ios::out);

        if (file.is_open()) {
            // Write header columns
            for (int c = 0; c < colNames_.size(); c++) {
                if (c != 0) {
                    file << delimiter;
                }
                file << colNames_[c];
            }
            file << '\n';

            // Get each row
            for (int r = 0; r < rowSize_; r++) {
                vector<Cell> row = (*this)[r];

                // Write each column
                for (int c = 0; c < colSize_; c++) {
                    // Escape delimiter if present in val
                    string value = row[c].value();
                    if (value.find(delimiter) != std::string::npos) {
                        value = escape + value + escape;
                    }

                    if (c != 0) {
                        file << delimiter;
                    }
                    file << value;
                }

                file << '\n';
            }

            file.close();
        }
    }


private:
    unordered_map< string, vector<Cell> > cols_;
    vector<string> colNames_;
    int colSize_;
    int rowSize_;

    void addColumn(const string name) {
        cols_[name] = vector<Cell>();
        colNames_.push_back(name);
        colSize_ += 1;
    }

    void addValue(const string column, const string value) {
        cols_[column].push_back(Cell(value));
        rowSize_ = cols_[column].size();
    }
};
