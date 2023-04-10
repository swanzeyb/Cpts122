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
#include "LinkedList.h"
#include "Record.h"
#include "DateTime.h"
#include "Table.h"
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

    Table table;
    table.readCSV("classList.csv");

    cout << table["Name"][0].value() << endl;
    cout << table["Name"][3].value() << endl;

    table.writeCSV("master.csv");

    LinkedList<Record> list;
    table.convert<Record>()
        .bindColumn("ID", &Record::setId)
        .bindColumn("Name", &Record::setName)
        .bindColumn("Email", &Record::setEmail)
        .bindColumn("Units", &Record::setUnits)
        .bindColumn("Program", &Record::setProgram)
        .bindColumn("Level", &Record::setLevel)
        .toLinkedList(list);

    waitForEnter();
    return 0;
}
