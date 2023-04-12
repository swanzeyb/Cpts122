
#include "Table.h"

Table::Table(): cols_(), colNames_(), colSize_(0), rowSize_(0) {}
Table::~Table() {}

Col Table::operator[](const string& colName) {
    int count = cols_.count(colName);
    if (cols_.count(colName) == 0) {
        addColumn(colName);
    }
    Col col(cols_[colName], colName);
    return col;
}

Row Table::operator[](const int& rowIndex) {
    Row row(*this, rowIndex);
    for (const string colName: colNames_) {
        row.push_back(&cols_[colName][rowIndex]);
    }
    return row;
}

// Iterator for each row in the table
class Table::Iterator {
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

Table::Iterator Table::begin() {
    return Iterator(*this, 0);
}

Table::Iterator Table::end() {
    return Iterator(*this, rowSize_);
}

int Table::rowSize() const {
    return rowSize_;
}

int Table::colSize() const {
    return colSize_;
}

vector<string>& Table::colNames() {
    return colNames_;
}

bool Table::exists(const string& key) {
    return find(colNames_.begin(), colNames_.end(), key) != colNames_.end();
}

bool Table::exists(const int& key) {
    return key > rowSize_ || key < 0;
}

void Table::addColumn(const string& name) {
    if (!exists(name)) {
        cols_[name] = vector<Cell>();
        colNames_.push_back(name);
        colSize_ += 1;
    }
}

void Table::addValue(const string& column, string& value) {
    int rowIndex = cols_[column].size();
    cols_[column].push_back(Cell(value, rowIndex));
    rowSize_ = rowIndex + 1;
}

void Table::readCSV(const string& filePath, const char delimiter, const char escape) {
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

void Table::writeCSV(const string& filePath, const char delimiter, const char escape) {
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
            Row row = (*this)[r];

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
