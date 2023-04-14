
#include "Table.h"

Table::Table(): cols_(), colNames_(), colSize_(0), rowSize_(0) {}
Table::~Table() {}

Col Table::operator[](const string& colName) {
    if (!cols_.count(colName)) {
        addColumn(colName);
    }
    Col col(cols_[colName], colName);
    return col;
}

Row Table::operator[](const int& rowIndex) {
    Row row(*this, rowIndex);
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

Table* Table::select(const vector<string>& colNames) {
    Table* table = new Table();
    for (const string& colName: colNames) {
        table->addColumn(colName);
    }

    for (const string colName: colNames) {
        for (int r = 0; r < rowSize_; r++) {
            table->addValue(colName, (*this)[colName][r].value());
        }
    }

    return table;
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
                } else if ((c == delimiter || c == '\r' || c == '\n' || ss.peek() == EOF) && !escapedCol) {
                    // At the end of the column value

                    // Windows stringstream handles EOF differently than the Mac implementation :(
                    #ifdef _WIN32
                    if (ss.peek() == EOF) {
                        value += c;
                    }
                    #endif

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

void Table::writeCSV(const string& filePath, const char delimiter, const char escape) const {
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
            // Write each column
            for (int c = 0; c < colSize_; c++) {
                const string& value = cols_.at(colNames_[c])[r].value();

                if (c != 0) {
                    file << delimiter;
                }

                // Escape delimiter if present in val
                if (value.find(delimiter) != std::string::npos) {
                    file << escape << value << escape;
                } else {
                    file << value;
                }
            }

            file << '\n';
        }

        file.close();
    }
}
