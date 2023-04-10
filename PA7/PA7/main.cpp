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
using std:: cin;
using std::endl;
using std::fstream;

void waitForEnter() {
    cout << std::endl << "Press enter to continue...";
    cin.ignore();
    cin.get();
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

    cout << table["Name"][0] << endl;
    cout << table["Name"][3] << endl;

    table.writeCSV("master.csv");

    cout << DateTime() << endl;

    LinkedList<Record> list;
    table.convert<Record>()
        .bindColumn("ID", &Record::setId)
        .bindColumn("Name", &Record::setName)
        .bindColumn("Email", &Record::setEmail)
        .bindColumn("Units", &Record::setUnits)
        .bindColumn("Program", &Record::setProgram)
        .bindColumn("Level", &Record::setLevel)
        .toLinkedList(list);

    cout << endl;
    list.print();

    waitForEnter();
    return 0;
}
