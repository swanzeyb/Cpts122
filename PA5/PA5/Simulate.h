/**
 * @file Simulate.h
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @brief Driver code for the grocery store line simulation.
 * @date 2023-03-11
 */

#pragma once
#include "Queue.h"

/**
 *  @class Simulate
 *  @brief Driver code to perform the simulation.
 * 
 *  1. Generate a random number between 1 – 5 and 3 – 8 for express and
 *  normal lanes, respectively. This represents the arrival time of the first
 *  customer into each lane. Set the variable for total time elapsed to 0.
 *
 *  2. As customers arrive into each line, randomly generate a service time
 *  for each. Start processing the customers in the lanes based on service
 *  time. Randomly generate the arrival time of the next customer into
 *  each line. Elapsed time should be updated by one unit.
 *
 *  3. As each minute elapses, a new customer may arrive and/or another
 *  customer may be done checking out. Display the appropriate
 *  messages as described above.
 *
 *  4. For every 10 minutes, print out the entire queue for each line.
 *
 *  5. Repeat steps 2 through 4 for n minutes of simulation.
 */
class Simulate {
    public:
        Simulate();
        ~Simulate();
        void runSimForNMinutes(int n);
        void runSimForNMinutes();
        static int getRandomNumber(int min, int max);
    private:
        void runSim(int n);
        Queue expressLane;
        Queue regularLane;
};
