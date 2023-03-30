/**
 * @file Simulate.h
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @brief Driver code for the grocery store line simulation.
 * @date 2023-03-11
 */

#include "Simulate.h"
#include "Queue.h"

Simulate::Simulate() {
    this->expressLane = Queue();
    this->regularLane = Queue();
}

Simulate::~Simulate() {
}

/**
 * @brief Get a random number between min and max
 * 
 * @param int min 
 * @param int max 
 * @return int 
 */
int Simulate::getRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

/**
 * @brief Runs the simulation for n minutes
 * Ask the user how many minutes they would like to run the simulation.
 */
void Simulate::runSimForNMinutes() {
    int n = 0;
    std::cout << "How many minutes would you like to run the simulation? ";
    std::cin >> n;
    std::cout << std::endl << "Running simulation for " << n << " minutes." << std::endl;
    this->runSim(n);
}

/**
 * @brief Runs the simulation for n minutes
 * Runs the sim for the number of minutes specified.
 * @param int n 
 */
void Simulate::runSimForNMinutes(int n) {
    std::cout << "Running simulation for " << n << " minutes." << std::endl;
    this->runSim(n);
}

/**
 * @brief Internal function to run the simulation
 * 
 * @param int n 
 */
void Simulate::runSim(int n) {
    Customer *expressCustomer = nullptr;
    Customer *regularCustomer = nullptr;

    // Generate a random number between 1 – 5 and 3 – 8 for express and regular lanes
    int expressArrivalTime = Simulate::getRandomNumber(1, 5);
    int regularArrivalTime = Simulate::getRandomNumber(3, 8);

    // Start the simulation
    for (int t = 1; t <= n; t++) {
        // One minute of time elapsed

        if (t == expressArrivalTime) {
            // A new customer has arrived in the express lane
            Customer *newExpressCustomer = new Customer(EXPRESS);
            newExpressCustomer->setServiceTime(Simulate::getRandomNumber(1, 6));
            this->expressLane.enqueue(newExpressCustomer);
            expressArrivalTime = t + Simulate::getRandomNumber(1, 5);

            // Set the current express customer if null
            if (expressCustomer == nullptr) {
                expressCustomer = this->expressLane.peek();
            }

            // Print the customer's arrival
            std::cout
                << "Express Lane: Customer "
                << newExpressCustomer->getCustomerNumber()
                << " arrived at "
                << t
                << " minute."
                << std::endl;
        }

        if (t == regularArrivalTime) {
            // A new customer has arrived in the regular lane
            Customer *newRegularCustomer = new Customer(REGULAR);
            newRegularCustomer->setServiceTime(Simulate::getRandomNumber(1, 12));
            this->regularLane.enqueue(newRegularCustomer);
            regularArrivalTime = t + Simulate::getRandomNumber(3, 8);

            // Set the current regular customer if null
            if (regularCustomer == nullptr) {
                regularCustomer = this->regularLane.peek();
            }

            // Print the customer's arrival
            std::cout
                << "Regular Lane: Customer "
                << newRegularCustomer->getCustomerNumber()
                << " arrived at "
                << t
                << " minute."
                << std::endl;
        }

        if (expressCustomer != nullptr) {
            // A customer is being serviced in the express lane
            expressCustomer->setServiceTime(expressCustomer->getServiceTime() - 1);
            expressCustomer->setTotalTime(expressCustomer->getTotalTime() + 1);
            if (expressCustomer->getServiceTime() == 0) {
                // The customer is done being serviced
                std::cout
                    << "Express Lane: Customer "
                    << expressCustomer->getCustomerNumber()
                    << " finished checking out with a total time of "
                    << expressCustomer->getTotalTime() << " minutes."
                    << std::endl;

                this->expressLane.dequeue();
                delete expressCustomer;
                expressCustomer = this->expressLane.peek();
            }
        }

        if (regularCustomer != nullptr) {
            // A customer is being serviced in the regular lane
            regularCustomer->setServiceTime(regularCustomer->getServiceTime() - 1);
            regularCustomer->setTotalTime(regularCustomer->getTotalTime() + 1);
            if (regularCustomer->getServiceTime() == 0) {
                // The customer is done being serviced
                std::cout
                    << "Regular Lane: Customer "
                    << regularCustomer->getCustomerNumber()
                    << " finished checking out with a total time of "
                    << regularCustomer->getTotalTime() << " minutes."
                    << std::endl;
                
                this->regularLane.dequeue();
                delete regularCustomer;
                regularCustomer = this->regularLane.peek();
            }
        }

        if (t % 10 == 0) {
            // Print the queues every 10 minutes
            std::cout << std::endl << "Express Lane -> ";
            this->expressLane.printQueue();
            std::cout << "Regular Lane -> ";
            this->regularLane.printQueue();
            std::cout << std::endl;
        }
    }

    // Reset the queues
    Customer::resetCount();
}
