/**
 * @file Record.h
 * @brief An object to hold student information
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <iostream>
#include <string>
#include "Stack.h"

using std::string;
using std::ostream;
using std::endl;

class Record {
public:
    Record(int id) : id(id), name(""), email(""), units(0), program(""), level("") {}
    Record() : id(0), name(""), email(""), units(0), program(""), level("") {}
    ~Record() {}

    /**
     * @brief Copy constructor
     * 
     * @param other 
     * @return Record& 
     */
    Record& operator=(const Record& other) {
        id = other.id;
        name = other.name;
        email = other.email;
        units = other.units;
        program = other.program;
        level = other.level;
        return *this;
    }

    /**
     * @brief Equality operator
     * 
     * Evaluates if two records are equal by comparing their IDs.
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    friend bool operator==(const Record& lhs, const Record& rhs) {
        return lhs.id == rhs.id;
    }

    /**
     * @brief Inequality operator
     * 
     * Evaluates if two records are not equal by comparing their IDs.
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    friend bool operator!=(const Record& lhs, const Record& rhs) {
        return !(lhs == rhs);
    }

    /**
     * @brief Stream insertion operator
     * 
     * @param lhs 
     * @param record 
     * @return ostream& 
     */
    friend ostream& operator<<(ostream& lhs, const Record& record) {
        lhs << record.id << " " << record.name << " " << record.email << " " << record.units << " " << record.program << " " << record.level << endl;
        return lhs;
    }
    
    /**
     * @brief Get the student's ID
     * 
     * @return int 
     */
    int getId() const;

    /**
     * @brief Set the student's ID
     * 
     * @param id 
     */
    void setId(int id);

    /**
     * @brief Get the student's Name
     * 
     * @return string 
     */
    string getName() const;

    /**
     * @brief Sets the student's name
     * 
     * @param name 
     */
    void setName(string name);

    /**
     * @brief Gets the student's email
     * 
     * @return string 
     */
    string getEmail() const;
    
    /**
     * @brief Sets the student's email
     * 
     * @param email 
     */
    void setEmail(string email);

    /**
     * @brief Get the students number of units
     * 
     * @return int 
     */
    int getUnits() const;

    /**
     * @brief Set the student's number of units
     * 
     * @param units 
     */
    void setUnits(int units);

    /**
     * @brief Gets which program the student is in
     * 
     * @return string 
     */
    string getProgram() const;

    /**
     * @brief Set which program the student is in
     * 
     * @param program 
     */
    void setProgram(string program);

    /**
     * @brief Get the student's class standing
     * 
     * @return string 
     */
    string getLevel() const;

    /**
     * @brief Set the student's class standing
     * 
     * @param level 
     */
    void setLevel(string level);
    
    /**
     * @brief Returns the student's absences
     * 
     * @return Stack<string>& 
     */
    Stack<string>& absences();

private:
    int id;
    string name;
    string email;
    int units;
    string program;
    string level;
    Stack<string> absences_;
};
