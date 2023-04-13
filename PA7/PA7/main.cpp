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
            case 1: {
                table.readCSV("classList.csv");
                list.clear();
                tableToLinkedList(table, list);
                table.writeCSV("master.csv");
                cout << "Read course file and overwrote master file." << endl;
                break;
            }
            case 2: {
                table.readCSV("master.csv");
                list.clear();
                tableToLinkedList(table, list);
                cout << "Populated the master list with the master file." << endl;
                break;
            }
            case 3: {
                table.writeCSV("master.csv");
                cout << "Written the master list to the master file." << endl;
                break;
            }
            case 4: {
                cout << "Marking absent students..." << endl << endl;
                const string& today = DateTime().toString();

                Node<Record>* current = list.getHead();
                while(current != nullptr) {
                    cout << current->data.getName() << endl;
                    cout << "Is this student present? (y/n): ";
                    char answer;
                    cin >> answer;
                    cout << endl;

                    const int& row = table.where("ID", current->data.getId()).getRow();
                    if (answer == 'n') {
                        current->data.absences().push(today);
                        table[row]["Absences"] = to_string(current->data.absences().size());
                        cout << "Marked " << current->data.getName() << "absent on " << DateTime().toString() << endl;
                    }
                    
                    cout << endl;
                    current = current->next;
                };
                
                table["Absences"].setNAValue("0");
                break;
            }
            case 5: {
                cout << "Not implemented." << endl;
                break;
            }
            case 6: {
                cout << "Generate absences report..." << endl << endl;
                int choice = 0;
                while(choice < 1) {
                    cout << "Which kind of report do you want to generate?" << endl;
                    cout << "1. Absences for all students." << endl;
                    cout << "2. Absences over a certain number of days." << endl;
                    int answer;
                    cin >> answer;
                    if (answer > 2 || answer < 1) {
                        cout << "Invalid choice." << endl;
                    } else {
                        choice = answer;
                    }
                }
                if (choice == 1) {
                    Table* absences = table.select({"ID", "Name", "Absences"});

                    // Add the date of the most recent absence
                    Node<Record>* record;
                    for (int i = 0; i < absences->rowSize(); i++) {
                        int id = (*absences)[i]["ID"].value<int>();
                        record = list.find(Record(id));
                        if (record != nullptr) {
                            Stack<string>& absStack = record->data.absences();
                            if (absStack.size() > 0) {
                                (*absences)[i]["Last Absence"] = absStack.peek();
                            }
                        }
                    }

                    (*absences)["Last Absence"].setNAValue("None");
                    absences->writeCSV("absences.csv");
                    delete absences;
                    absences = nullptr;
                } else {
                    int days = 0;
                    while(days < 1) {
                        cout << "Generate report of students absent more than: ";
                        int answer;
                        cin >> answer;
                        cout << " days." << endl;
                        if (answer < 1) {
                            cout << "Invalid choice." << endl;
                        } else {
                            days = answer;
                        }
                    }

                    Table* absences = table.select({"ID", "Name", "Absences"});

                    // Add the date of the most recent absence
                    Node<Record>* record;
                    for (int i = 0; i < absences->rowSize(); i++) {
                        int id = (*absences)[i]["ID"].value<int>();
                        record = list.find(Record(id));
                        if (record != nullptr) {
                            Stack<string>& absStack = record->data.absences();
                            if (absStack.size() > days) {
                                (*absences)[i]["Last Absence"] = absStack.peek();
                            }
                        }
                    }

                    (*absences)["Last Absence"].setNAValue("None");
                    absences->writeCSV("absences.csv");
                    delete absences;
                    absences = nullptr;
                }
                break;
            }
            case 7:
                return 0;
            default:
                cout << "Invalid choice" << endl;
                break;
        }

        Menu::waitForEnter();
    }

    return 0;
}
