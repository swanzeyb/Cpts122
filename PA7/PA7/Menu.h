/**
 * @file Menu.h
 * @brief Static class to handle menu display and input
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Menu {
public:
    Menu() {};
    ~Menu() {};

    /**
     * @brief Waits for the user to press enter
     * 
     */
    static void waitForEnter() {
        cout << std::endl << "Press enter to continue...";
        cin.ignore();
        cin.get();
    }

    /**
     * @brief Clears the terminal
     * 
     */
    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #elif __APPLE__
            system("clear");
        #endif
    }

    /**
     * @brief Prints the menu choices
     * 
     */
    static void print() {
        cout << "1. Import course list" << endl;
        cout << "2. Load master list" << endl;
        cout << "3. Store master list" << endl;
        cout << "4. Mark absences" << endl;
        cout << "5. Edit absences" << endl;
        cout << "6. Generate report" << endl;
        cout << "7. Exit" << endl;
    }

    /**
     * @brief Gets the user's choice
     * 
     * @return int 
     */
    static int eval() {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

private:
};
