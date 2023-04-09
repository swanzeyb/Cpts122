
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
using std::string;
using std::stringstream;
using std::to_string;
using std::fstream;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;

class Cell {
public:
    Cell(): value_() {}
    Cell(const string& value): value_(value) {}

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

class Table {
public:
    Table() {}
    
    const vector<Cell>& operator[](string col) {
        return cols_[col];
    }

    void readCSV(const string filePath, const char delimiter = ',', const char escape = '"') {
        fstream file;
        file.open(filePath);

        if (file.is_open()) {
            char c;
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
                    if (c == '\r' || c == '\n') {
                        value = "";
                        continue;
                    } else if (c == escape) {
                        escapedCol = !escapedCol;
                    } else if (c == delimiter && !escapedCol) {
                        // At the end of the column value

                        // Setup our columns
                        if (rowIndex == 0) {
                            if (value == "") {
                                if (!cols_.count("index_")) {
                                    cols_["index_"] = vector<Cell>();
                                    colNames_.push_back("index_");
                                } else {
                                    string colName = "Col " + to_string(colIndex);
                                    cols_[colName] = vector<Cell>();
                                    colNames_.push_back(colName);
                                }
                            } else {
                                cols_[value] = vector<Cell>();
                                colNames_.push_back(value);
                            }
                        } else {
                            // Save the read data
                            string colName = colNames_[colIndex];

                            if (escapedCol && cols_[colName].size() == rowIndex) {
                                // If we already inserted data for this escaped col, append
                                Cell& cell = cols_[colName][rowIndex - 1]; // Subtract 1 from rowIndex because header row
                                cell.value(cell.value() + " " + value);
                            } else {
                                cols_[colName].push_back(Cell(value));
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

    void writeCSV(string filePath, char delimiter = ',', char quote = '"') const {

    }


private:
    unordered_map< string, vector<Cell> > cols_;
    vector<string> colNames_;
};
