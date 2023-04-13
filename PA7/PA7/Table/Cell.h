
#pragma once

#include <string>
#include <sstream>

using std::string;
using std::to_string;
using std::stringstream;

class Cell {
public:
    Cell(int row);
    Cell(const string& value, int row);
    Cell(string& value, int row);
    ~Cell();

    /**
     * @brief Overload the = operator to set the value of the cell
     * 
     * @param value 
     */
    void operator=(const string& value);

    /**
     * @brief Overload the = operator to set the value of the cell
     * 
     * @tparam T 
     * @param value 
     */
    template <typename T>
    void operator=(const T& value) {
        value_ = to_string(value);
    }

    /**
     * @brief Sets the value of the cell
     * 
     * @param value 
     */
    void value(const string& value);

    /**
     * @brief Returns the value of the cell
     * 
     * @tparam T return type
     * @return T 
     */
    template<typename T>
    T value() const {
        return Cell::parse<T>(value_);
    }

    /**
     * @brief Returns the value of the cell
     * 
     * @return string 
     */
    string value() const;

    /**
     * @brief Returns a reference to the value of the cell
     * 
     * @return string& 
     */
    string& value();

    /**
     * @brief Returns which row the cell belongs to
     * 
     * @return int 
     */
    int& getRow();

    /**
     * @brief Sets which row the cell belongs to
     * 
     * @param row 
     */
    void setRow(const int& row);

    /**
     * @brief Sets what value to return if the cell is empty
     * 
     * @param value 
     */
    void setNAValue(const string& value);

private:
    string value_;
    int row_;

    /**
     * @brief Trys to parse a string into a desired type
     * 
     * @tparam T type to convert string to
     * @param str 
     * @return T 
     */
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
