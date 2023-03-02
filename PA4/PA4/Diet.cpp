
#include "Diet.hpp"

DietPlan::DietPlan (int goalCalories, string planName, string date) {
    this->goal = goalCalories;
    this->name = planName;
    this->date = date;
}

DietPlan::DietPlan (const DietPlan &copy) {
    this->goal = copy.goal;
    this->name = copy.name;
    this->date = copy.date;
}

DietPlan::~DietPlan () {}

void DietPlan::setGoal(int goalCalories) {
    this->goal = goalCalories;
}

void DietPlan::setName(string planName) {
    this->name = planName;
}

void DietPlan::setDate(string date) {
    this->date = date;
}

int DietPlan::getGoal() {
    return this->goal;
}

string DietPlan::getName() {
    return this->name;
}

string DietPlan::getDate() {
    return this->date;
}

DietPlan &DietPlan::operator= (const DietPlan &rhs) {
    this->goal = rhs.goal;
    this->name = rhs.name;
    this->date = rhs.date;
    return *this;
}

ostream &operator<< (ostream &lhs, const DietPlan &rhs) {
    lhs << rhs.name << " " << rhs.goal << " " << rhs.date;
    return lhs;
}

istream &operator>> (istream &lhs, DietPlan &rhs) {
    lhs >> rhs.name >> rhs.goal >> rhs.date;
    return lhs;
}
