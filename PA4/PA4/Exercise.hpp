
#include <iostream>
#include <string>

using namespace std;

class ExercisePlan {
  private:
    int goal;
    string name;
    string date;
  public:
    ExercisePlan(int newGoalSteps = 0, string newName = " ", string newDate = " ");
    ExercisePlan(ExercisePlan &copy);
    ~ExercisePlan();
    void editGoal();
    int getGoal();
    string getName();
    string getDate();
    void setGoal(int newGoalSteps);
    void setName(string newName);
    void setDate(string newDate);
    ExercisePlan &operator=(const ExercisePlan &rhs);
    friend ostream &operator<<(ostream &lhs, const ExercisePlan &rhs);
    friend istream &operator>>(istream &lhs, ExercisePlan &rhs);
};
