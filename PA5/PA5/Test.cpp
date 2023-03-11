/**
 * @file Test.cpp
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @brief Implements unit tests of our queue and simulation.
 * @date 2023-03-10
 */

#include "Test.h"
UTEST_STATE();

#include "Queue.h"

/**
 * @brief Test case that executes enqueue() operation on an empty queue
 */
UTEST(Enqueue, InsertOneNode) {
    Queue *pQueue = new Queue();
    Data *pData = new Data();
    pQueue->enqueue(pData);
    ASSERT_EQ(pQueue->dequeue(), pData);
    delete pQueue;
    delete pData;
}

/**
 * @brief Test case that executes enqueue() operation on a non-empty queue
 */
UTEST(Enqueue, InsertTwoNodes) {
    Queue *pQueue = new Queue();
    Data *pData1 = new Data();
    Data *pData2 = new Data();
    pQueue->enqueue(pData1);
    pQueue->enqueue(pData2);
    ASSERT_EQ(pQueue->dequeue(), pData1);
    ASSERT_EQ(pQueue->dequeue(), pData2);
    delete pQueue;
    delete pData1;
    delete pData2;
}

/**
 * @brief Test case that executes dequeue() operation on a length one queue
 */
UTEST(Dequeue, OneNodeQueue) {
    Queue *pQueue = new Queue();
    Data *pData = new Data();
    pQueue->enqueue(pData);
    ASSERT_EQ(pQueue->dequeue(), pData);
    delete pQueue;
    delete pData;
}

/**
 * @brief Test case that executes dequeue() operation on a length two queue
 */
UTEST(Dequeue, TwoNodeQueue) {
    Queue *pQueue = new Queue();
    Data *pData1 = new Data();
    Data *pData2 = new Data();
    pQueue->enqueue(pData1);
    pQueue->enqueue(pData2);
    ASSERT_EQ(pQueue->dequeue(), pData1);
    ASSERT_EQ(pQueue->dequeue(), pData2);
    delete pQueue;
    delete pData1;
    delete pData2;
}

int RunTests(int argc, const char *const argv[]) {
  return utest_main(argc, argv);
}
