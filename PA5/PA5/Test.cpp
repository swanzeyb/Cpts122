/**
 * @file Test.cpp
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @brief Implements unit tests of our queue and simulation.
 * @date 2023-03-10
 */

#include "Test.h"
UTEST_STATE();

#include "Queue.h"
#include "Simulate.h"

/**
 * @brief Test case that executes enqueue() operation on an empty queue
 */
UTEST(Enqueue, InsertOneNode) {
    Queue *pQueue = new Queue();
    Customer *pData = new Customer(EXPRESS);
    pQueue->enqueue(pData);
    ASSERT_EQ(pQueue->dequeue(), pData);
    delete pQueue;
    delete pData;
    Customer::resetCount();
}

/**
 * @brief Test case that executes enqueue() operation on a non-empty queue
 */
UTEST(Enqueue, InsertTwoNodes) {
    Queue *pQueue = new Queue();
    Customer *pData1 = new Customer(EXPRESS);
    Customer *pData2 = new Customer(EXPRESS);
    pQueue->enqueue(pData1);
    pQueue->enqueue(pData2);
    ASSERT_EQ(pQueue->dequeue(), pData1);
    ASSERT_EQ(pQueue->dequeue(), pData2);
    delete pQueue;
    delete pData1;
    delete pData2;
    Customer::resetCount();
}

/**
 * @brief Test case that executes dequeue() operation on a length one queue
 */
UTEST(Dequeue, OneNodeQueue) {
    Queue *pQueue = new Queue();
    Customer *pData = new Customer(EXPRESS);
    pQueue->enqueue(pData);
    ASSERT_EQ(pQueue->dequeue(), pData);
    delete pQueue;
    delete pData;
    Customer::resetCount();
}

/**
 * @brief Test case that executes dequeue() operation on a length two queue
 */
UTEST(Dequeue, TwoNodeQueue) {
    Queue *pQueue = new Queue();
    Customer *pData1 = new Customer(EXPRESS);
    Customer *pData2 = new Customer(EXPRESS);
    pQueue->enqueue(pData1);
    pQueue->enqueue(pData2);
    ASSERT_EQ(pQueue->dequeue(), pData1);
    ASSERT_EQ(pQueue->dequeue(), pData2);
    delete pQueue;
    delete pData1;
    delete pData2;
    Customer::resetCount();
}

/** 
 * @brief Run the simulation in a test case for 24 hrs
 */   
UTEST(Simulate, RunSim) {
    std::cout.setstate(std::ios_base::failbit); // Don't print while testing
    Simulate *sim = new Simulate();
    sim->runSimForNMinutes(24 * 60);
    delete sim;
    std::cout.clear(); // Restore printing
}

/**
 * @brief Runs all unit tests
 * 
 * @param argc Pass this from main
 * @param argv Pass this from main
 * @return int Success code
 */
int RunTests(int argc, const char *const argv[]) {
  return utest_main(argc, argv);
}
