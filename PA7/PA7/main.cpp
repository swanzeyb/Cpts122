/**
 * @file Main.cpp
 * @brief Uses a binary search tree to convert a text file to morse code
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "Record.h"
#include "DateTime.h"
#include "Table/Table.h"
#include "Table/Row.h"
#include "Menu.h"

using std::string;
using std::cout;
using std:: cin;
using std::endl;
using std::fstream;

void tableToLinkedList(Table& table, LinkedList<Record>& list) {
    table.convert<Record>()
        .bindColumn("ID", &Record::setId)
        .bindColumn("Name", &Record::setName)
        .bindColumn("Email", &Record::setEmail)
        .bindColumn("Units", &Record::setUnits)
        .bindColumn("Program", &Record::setProgram)
        .bindColumn("Level", &Record::setLevel)
        .toLinkedList(list);
}

int main(int argc, const char *const argv[])
{
    Table table;
    LinkedList<Record> list;
    int choice;

    while(true) {
        Menu::clearScreen();
        Menu::print();
        cout << endl;
        choice = Menu::eval();
        Menu::clearScreen();

        switch(choice) {
            case 1:
                table.readCSV("classList.csv");
                list.clear();
                tableToLinkedList(table, list);
                table.writeCSV("master.csv");
                cout << "Read course file and overwrote master file." << endl;
                break;
            case 2:
                table.readCSV("master.csv");
                list.clear();
                tableToLinkedList(table, list);
                cout << "Populated the master list with the master file." << endl;
                break;
            case 3:
                table.writeCSV("master.csv");
                cout << "Written the master list to the master file." << endl;
                break;
            case 4:
                cout << "Marking absent students..." << endl << endl;
                const string& today = DateTime().toString();
                Node<Record>* current = list.getHead();
                while(current != nullptr) {
                    cout << current->data.getName() << endl;
                    cout << "Is this student present? (y/n): ";
                    char answer;
                    cin >> answer;
                    cout << endl;
                    if (answer == 'n') {
                        current->data.absences().push(today);
                        const int row = table.where("ID", current->data.getId()).getRow();
                        table[row]["Absences"] = today;

                        cout << "Marked " << current->data.getName() << "absent on " << DateTime().toString() << endl;
                    }
                    cout << endl;
                    current = current->next;
                }
                break;
            // case 5:
            //     cout << "Not implemented." << endl;
            //     break;
            // case 6:
            //     break;
            // case 7:
            //     return 0;
            // default:
            //     cout << "Invalid choice" << endl;
            //     break;
        }

        Menu::waitForEnter();
    }

    return 0;
}
