
#include "App.hpp"
#include <iostream>

FitnessAppWrapper::FitnessAppWrapper() {
    dietIn.open("dietPlans.txt", ios::in);
    dietOut.open("dietPlans.txt", ios::app);
    exerciseIn.open("exercisePlans.txt", ios::in);
    exerciseOut.open("exercisePlans.txt", ios::app);
}

FitnessAppWrapper::~FitnessAppWrapper() {
    dietIn.close();
    dietOut.close();
    exerciseIn.close();
    exerciseOut.close();
}

void FitnessAppWrapper::waitForInput() {
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void FitnessAppWrapper::displayMenu() {
    cout << "Fitness Application Menu" << endl;
    cout << "1. Load weekly diet and exercise plan from file" << endl;
    cout << "2. Store weekly diet and exercise plan to file" << endl;
    cout << "3. Display weekly diet and exercise plan to screen" << endl;
    cout << "4. Edit daily diet and exercise plan" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void FitnessAppWrapper::runApp() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                loadWeeklyPlan(dietIn, dietPlan);
                loadWeeklyPlan(exerciseIn, exercisePlan);
                waitForInput();
                break;
            case 2:
                storeWeeklyPlan(dietOut, dietPlan);
                storeWeeklyPlan(exerciseOut, exercisePlan);
                waitForInput();
                break;
            case 3:
                displayWeeklyPlan(dietPlan);
                displayWeeklyPlan(exercisePlan);
                waitForInput();
                break;
            case 4:
                editDailyPlan(dietPlan);
                editDailyPlan(exercisePlan);
                waitForInput();
                break;
            case 5:
                break;
        }
        system("clear");
    } while (choice != 5);
}

void FitnessAppWrapper::loadDailyPlan(fstream &fileStream, DietPlan &plan) {
    string name;
    string garbage;
    int goal;
    string date;

    getline(fileStream, name);
    fileStream >> goal >> date;
    getline(fileStream, garbage);

    plan.setName(name);
    plan.setGoal(goal);
    plan.setDate(date);
}

void FitnessAppWrapper::loadDailyPlan(fstream &fileStream, ExercisePlan &plan) {
    string name;
    string garbage;
    int goal;
    string date;

    getline(fileStream, name);
    fileStream >> goal >> date;
    getline(fileStream, garbage);

    plan.setName(name);
    plan.setGoal(goal);
    plan.setDate(date);
}

void FitnessAppWrapper::loadWeeklyPlan(fstream &fileStream, DietPlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        loadDailyPlan(fileStream, weeklyPlan[i]);
    }
}

void FitnessAppWrapper::loadWeeklyPlan(fstream &fileStream, ExercisePlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        loadDailyPlan(fileStream, weeklyPlan[i]);
    }
}

void FitnessAppWrapper::displayDailyPlan(DietPlan &plan) {
    cout << plan << endl;
}

void FitnessAppWrapper::displayDailyPlan(ExercisePlan &plan) {
    cout << plan << endl;
}

void FitnessAppWrapper::displayWeeklyPlan(DietPlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        displayDailyPlan(weeklyPlan[i]);
    }
}

void FitnessAppWrapper::displayWeeklyPlan(ExercisePlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        displayDailyPlan(weeklyPlan[i]);
    }
}

void FitnessAppWrapper::storeDailyPlan(fstream &fileStream, DietPlan &plan) {
    fileStream << plan.getName() << " " << plan.getGoal() << " " << plan.getDate() << endl;
}

void FitnessAppWrapper::storeDailyPlan(fstream &fileStream, ExercisePlan &plan) {
    fileStream << plan.getName() << " " << plan.getGoal() << " " << plan.getDate() << endl;
}

void FitnessAppWrapper::storeWeeklyPlan(fstream &fileStream, DietPlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        storeDailyPlan(fileStream, weeklyPlan[i]);
    }
}

void FitnessAppWrapper::storeWeeklyPlan(fstream &fileStream, ExercisePlan weeklyPlan[]) {
    for (int i = 0; i < 7; i++) {
        storeDailyPlan(fileStream, weeklyPlan[i]);
    }
}

void FitnessAppWrapper::editDailyPlan(DietPlan weeklyPlan[]) {
    int day;
    cout << "Enter day of plan to edit (1-7): ";
    cin >> day;
    cin.ignore();

    if (day < 1 || day > 7) {
        cout << "Invalid day. Try again." << endl;
        return;
    }

    DietPlan &plan = weeklyPlan[day - 1];
    string name;
    int goal;
    string date;

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter goal: ";
    cin >> goal;
    cin.ignore();

    cout << "Enter date: ";
    getline(cin, date);

    plan.setName(name);
    plan.setGoal(goal);
    plan.setDate(date);
}

void FitnessAppWrapper::editDailyPlan(ExercisePlan weeklyPlan[]) {
    int day;
    cout << "Enter day of plan to edit (1-7): ";
    cin >> day;
    cin.ignore();

    if (day < 1 || day > 7) {
        cout << "Invalid day. Try again." << endl;
        return;
    }

    ExercisePlan &plan = weeklyPlan[day - 1];
    string name;
    int goal;
    string date;

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter goal: ";
    cin >> goal;
    cin.ignore();

    cout << "Enter date: ";
    getline(cin, date);

    plan.setName(name);
    plan.setGoal(goal);
    plan.setDate(date);
}
