
#include "Record.h"

int Record::getId() const {
    return this->id;
}

string Record::getName() const {
    return this->name;
}

string Record::getEmail() const {
    return this->email;
}

int Record::getUnits() const {
    return this->units;
}

string Record::getProgram() const {
    return this->program;
}

string Record::getLevel() const {
    return this->level;
}

void Record::setId(int id) {
    this->id = id;
}

void Record::setName(string name) {
    this->name = name;
}

void Record::setEmail(string email) {
    this->email = email;
}

void Record::setUnits(int units) {
    this->units = units;
}

void Record::setProgram(string program) {
    this->program = program;
}

void Record::setLevel(string level) {
    this->level = level;
}
