/**
 * @file Main.cpp
 * @brief Uses a binary search tree to convert a text file to morse code
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include <iostream>
#include <string>
#include "List.h"
using std::string;
using std::cout;
using std::endl;

void waitForEnter() {
    std::cout << std::endl << "Press enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #endif
}

int main(int argc, const char *const argv[])
{
    clearScreen();

    cout << "Hello World." << endl;

    List<string> yup;
    yup.insertAtFront("Hi mom.");
    yup.print();

    waitForEnter();
    return 0;
}
