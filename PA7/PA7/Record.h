
#include <iostream>
#include <string>
#include "Stack.h"
using std::string;

class Record {
private:
    int id;
    string name;
    string email;
    int units;
    string program;
    string level;
    
public:
    Record() : id(0), name(""), email(""), units(0), program(""), level("") {}
    Record(int id, string name, string email, int units, string program, string level) : id(id), name(name), email(email), units(units), program(program), level(level) {}
    Record(const Record& other) : id(other.id), name(other.name), email(other.email), units(other.units), program(other.program), level(other.level) {}
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
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    string getEmail() const {
        return email;
    }
    int getUnits() const {
        return units;
    }
    string getProgram() const {
        return program;
    }
    string getLevel() const {
        return level;
    }
    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        this->name = name;
    }
    void setEmail(string email) {
        this->email = email;
    }
    void setUnits(int units) {
        this->units = units;
    }
    void setProgram(string program) {
        this->program = program;
    }
    void setLevel(string level) {
        this->level = level;
    }
    // friend std::ostream& operator<<(std::ostream& os, const Record& record) {
    //     os << record.id << " " << record.name << " " << record.email << " " << record.units << " " << record.program << " " << record.level;
    //     return os;
    // }
    // friend std::istream& operator>>(std::istream& is, Record& record) {
    //     is >> record.id >> record.name >> record.email >> record.units >> record.program >> record.level;
    //     return is;
    // }
    friend bool operator==(const Record& lhs, const Record& rhs) {
        return lhs.id == rhs.id;
    }
    friend bool operator!=(const Record& lhs, const Record& rhs) {
        return !(lhs == rhs);
    }
};
