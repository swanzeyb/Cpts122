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

    Table classList;
    classList.readCSV("classList.csv");

    cout << classList["Name"][0].value() << endl;
    cout << classList["Name"][3].value() << endl;

    // List<Record> classList;
    // fstream file;
    // file.open("classList.csv");

    // if (file.is_open()) {
    //     string line;
    //     string value;
    //     int index = 0;
    //     Record record;

    //     // Skip first line
    //     getline(file, line, '\r');

    //     while (getline(file, line, '\r')) {
    //         // Add the new record to the list
    //         if (index > 0) {
    //             classList.insertAtFront(record);
    //             index = 0;
    //         }

    //         stringstream ss(line);
    //         while (getline(ss, value, ',')) {
    //             // Increment index, skip csv index col
    //             if (++index == 1) {
    //                 continue;
    //             }

    //             // Strip newline characters
    //             if (value.find('\n') != std::string::npos) {
    //                 value = value.substr(1, value.length());
    //             }

    //             // Strip quotes
    //             if (value[0] == '"') {
    //                 value = value.substr(1, value.length() - 1);
    //                 cout << value << " ";
    //             } else if (value[value.length() - 1] == '"') {
    //                 value = value.substr(0, value.length() - 1);
    //                 cout << value << endl;
    //             } else {
    //                 cout << value << endl;
    //             }

    //             // Assign to record
    //             switch (index) {
    //                 case 2:
    //                     record.setId(std::stoi(value));
    //                     break;
    //                 case 3:
    //                     record.setName(value);
    //                     break;
    //                 case 4:
    //                     record.setName(value + " " + record.getName());
    //                     break;
    //                 case 5:
    //                     record.setEmail(value);
    //                     break;
    //                 case 6:
    //                     record.setUnits(std::stoi(value));
    //                     break;
    //                 case 7:
    //                     record.setProgram(value);
    //                     break;
    //                 case 8:
    //                     record.setLevel(value);
    //                     break;
    //             }
    //         }
    //     }
    // } else {
    //     cout << "File not found." << endl;
    // }

    waitForEnter();
    return 0;
}
