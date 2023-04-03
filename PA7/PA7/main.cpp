/**
 * @file Main.cpp
 * @brief Uses a binary search tree to convert a text file to morse code
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-21
 */

#include <iostream>
#include <vector>
#include "BST.h"
using std::cout;
using std::endl;
using std::vector;

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
    
    // Create and load Morse Code BST Tree
    BST morseTree;

    // Print the tree
    morseTree.print();
    cout << endl;

    // Load convert.txt and convert to Morse Code
    cout << "(Convert.txt)" << endl;
    fstream file;
    file.open("Convert.txt");

    vector<string> toConvert;
    while (!file.eof()) {
        string word;
        file >> word;
        toConvert.push_back(word);
        cout << word << " ";
    }
    cout << endl;
    file.close();

    // Uppercase all characters
    for (int i = 0; i < toConvert.size(); i++) {
        for (int j = 0; j < toConvert[i].size(); j++) {
            toConvert[i][j] = toupper(toConvert[i][j]);
        }
    }

    // Echoed to screen
    cout << endl << "(Echoed to screen)" << endl;
    for (int i = 0; i < toConvert.size(); i++) {
        for (int j = 0; j < toConvert[i].size(); j++) {
            cout << morseTree.search(toConvert[i][j]) << " ";
        }
        cout << "   ";
    }
    cout << endl;
    waitForEnter();

    return 0;
}
