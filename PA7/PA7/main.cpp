/**
 * @file Main.cpp
 * @brief Uses a binary search tree to convert a text file to morse code
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "List.h"
#include "Record.h"
#include "DateTime.h"
#include "CSV.h"
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::fstream;

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

    Table studentsTable;
    studentsTable.readCSV("classList.csv");

    cout << studentsTable["Name"][0].value() << endl;
    cout << studentsTable["Name"][3].value() << endl;

    studentsTable.writeCSV("master.csv");

    List<Record> studentsList;
    
    for (const Row& row : studentsTable) {
        const Cell& cell = row["Name"];
        cout << cell.value() << endl;
    }

    waitForEnter();
    return 0;
}
