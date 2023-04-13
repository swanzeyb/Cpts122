
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

    Record& operator=(const Record& other) {
        id = other.id;
        name = other.name;
        email = other.email;
        units = other.units;
        program = other.program;
        level = other.level;
        return *this;
    }
    friend bool operator==(const Record& lhs, const Record& rhs) {
        return lhs.id == rhs.id;
    }
    friend bool operator!=(const Record& lhs, const Record& rhs) {
        return !(lhs == rhs);
    }
    friend ostream& operator<<(ostream& lhs, const Record& record) {
        lhs << record.id << " " << record.name << " " << record.email << " " << record.units << " " << record.program << " " << record.level << endl;
        return lhs;
    }
    
    int getId() const;
    string getName() const;
    string getEmail() const;
    int getUnits() const;
    string getProgram() const;
    string getLevel() const;
    void setId(int id);
    void setName(string name);
    void setEmail(string email);
    void setUnits(int units);
    void setProgram(string program);
    void setLevel(string level);
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
