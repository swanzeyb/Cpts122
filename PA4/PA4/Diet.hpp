
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DietPlan {
	private:
    int goal;
    string name;
    string date;
	public:
    DietPlan(int goalCalories = 0, string planName = "", string date = "");
    DietPlan(const DietPlan &copy);
    ~DietPlan();
    void setGoal(int goalCalories);
    void setName(string planName);
    void setDate(string date);
    int getGoal();
    string getName();
    string getDate();
    DietPlan &operator=(const DietPlan &rhs);
    friend ostream& operator<<(ostream &lhs, DietPlan &rhs);
    friend ifstream& operator>>(ifstream &lhs, DietPlan &rhs);
};
