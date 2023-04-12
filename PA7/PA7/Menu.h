
#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Menu {
public:
    Menu() {};
    ~Menu() {};

    static void waitForEnter() {
        cout << std::endl << "Press enter to continue...";
        cin.ignore();
        cin.get();
    }

    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #elif __APPLE__
            system("clear");
        #endif
    }

    static void print() {
        cout << "1. Import course list" << endl;
        cout << "2. Load master list" << endl;
        cout << "3. Store master list" << endl;
        cout << "4. Mark absences" << endl;
        cout << "5. Edit absences" << endl;
        cout << "6. Generate report" << endl;
        cout << "7. Exit" << endl;
    }

    static int eval() {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

private:
};
