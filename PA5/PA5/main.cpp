
#include "Test.h"
#include "Simulate.h"
#include <iostream>

int main(int argc, const char *const argv[])
{
    while(true) {
        #ifdef _WIN32
            system("cls");
        #elif __APPLE__
            system("clear");
        #endif
        
        // Menu
        std::cout << "Main menu:" << std::endl;
        std::cout << "1. Run simulation for 24 hours" << std::endl;
        std::cout << "2. Run simulation for n minutes" << std::endl;
        std::cout << "3. Run unit tests" << std::endl;
        std::cout << "4. Exit" << std::endl;

        // Get choice
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        std::cout << std::endl;

        // Do action
        switch(choice) {
            case 1: {
                Simulate *sim = new Simulate();
                sim->runSimForNMinutes(24 * 60);
                delete sim;
                break;
            }
            case 2: {
                Simulate *sim = new Simulate();
                sim->runSimForNMinutes();
                delete sim;
                break;
            }
            case 3: {
                RunTests(argc, argv);
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                break;
            }
        }

        // Wait for user to press enter
        std::cout << std::endl << "Press enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
