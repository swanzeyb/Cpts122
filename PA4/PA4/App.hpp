
#include <iostream>
#include <string>
#include <fstream>
#include "Exercise.hpp"
#include "Diet.hpp"

using namespace std;

class FitnessAppWrapper {
  public:
    FitnessAppWrapper();
    ~FitnessAppWrapper();
    void runApp();
    void loadDailyPlan(fstream &fileStream, DietPlan &plan);
    void loadDailyPlan(fstream &fileStream, ExercisePlan &plan);
    void loadWeeklyPlan(fstream &fileStream, DietPlan weeklyPlan[]);
    void loadWeeklyPlan(fstream &fileStream, ExercisePlan weeklyPlan[]);
    void displayDailyPlan(DietPlan &plan);
    void displayDailyPlan(ExercisePlan &plan);
    void displayWeeklyPlan(DietPlan weeklyPlan[]);
    void displayWeeklyPlan(ExercisePlan weeklyPlan[]);
    void storeDailyPlan(fstream &fileStream, DietPlan &plan);
    void storeDailyPlan(fstream &fileStream, ExercisePlan &plan);
    void storeWeeklyPlan(fstream &fileStream, DietPlan weeklyPlan[]);
    void storeWeeklyPlan(fstream &fileStream, ExercisePlan weeklyPlan[]);
    void editDailyPlan(DietPlan weeklyPlan[]);
    void editDailyPlan(ExercisePlan weeklyPlan[]);
    void displayMenu();
  private:
    DietPlan dietPlan[7];
    ExercisePlan exercisePlan[7];
    fstream dietIn;
    fstream dietOut;
    fstream exerciseIn;
    fstream exerciseOut;
};
