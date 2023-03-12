/**
 * @file Queue.h
 * @brief A queue implementation for the line simulation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-10
 */

#pragma once
#include <iostream>

/**
 * @brief An enum to represent the type of lane
 */
enum LaneType {
    EXPRESS,
    REGULAR
};

/**
 * @class Customer
 * @brief Represents customer data
 */
class Customer {
    public:
        Customer(LaneType laneType);
        ~Customer();
        int getCustomerNumber();
        void setCustomerNumber(int customerNumber);
        int getServiceTime();
        void setServiceTime(int serviceTime);
        int getTotalTime();
        void setTotalTime(int totalTime);
        static void resetCount();
    private:
        LaneType laneType;
        static int expressCount;
        static int regularCount;
        int customerNumber;
        int serviceTime;
        int totalTime;
};

/**
 * @class QueueNode
 * @brief Represents a node in the queue
 * Also holds the customer data
 */
class QueueNode {
    public:
        QueueNode(Customer *pData);
        ~QueueNode();
        Customer *getData();
        void setData(Customer *pData);
        QueueNode *getNext();
        void setNext(QueueNode *pNext);
    private:
        Customer *pData;
        QueueNode *pNext;
};

/**
 * @class Queue
 * @brief A queue implementation using our simulation data
 * Uses linked lists internally to store the data
 */
class Queue {
    public:
        Queue();
        ~Queue();
        void enqueue(Customer *pData);
        Customer *dequeue();
        Customer *peek();
        void printQueue();
        bool isEmpty();
    private:
        QueueNode *pHead;
        QueueNode *pTail;
};
