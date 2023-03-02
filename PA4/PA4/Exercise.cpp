
#include "Exercise.hpp"

ExercisePlan::ExercisePlan (int newGoalSteps, string newName, string newDate) {
    this->goal = newGoalSteps;
    this->name = newName;
    this->date = newDate;
}

ExercisePlan::ExercisePlan (ExercisePlan &copy) {
    this->goal = copy.goal;
    this->name = copy.name;
    this->date = copy.date;
}

ExercisePlan::~ExercisePlan () {}

int ExercisePlan::getGoal() {
    return this->goal;
}

string ExercisePlan::getName() {
    return this->name;
}

string ExercisePlan::getDate() {
    return this->date;
}

void ExercisePlan::setName(string newName) {
    this->name = newName;
}

void ExercisePlan::setDate(string newDate) {
    this->date = newDate;
}

void ExercisePlan::setGoal(int newGoalSteps) {
    this->goal = newGoalSteps;
}

void ExercisePlan::editGoal() {
    int newGoal;
    cout << "Enter new goal: ";
    cin >> newGoal;
    setGoal(newGoal);
}

ExercisePlan &ExercisePlan::operator= (const ExercisePlan &rhs) {
    this->goal = rhs.goal;
    this->name = rhs.name;
    this->date = rhs.date;
    return *this;
}

ostream &operator<< (ostream &lhs, const ExercisePlan &rhs) {
    lhs << rhs.name << " " << rhs.goal << " " << rhs.date << endl;
    return lhs;
}

istream &operator>> (istream &lhs, ExercisePlan &rhs) {
    lhs >> rhs.name >> rhs.goal >> rhs.date;
    return lhs;
}
