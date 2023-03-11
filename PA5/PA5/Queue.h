/**
 * @file Queue.h
 * @brief A queue implementation for the line simulation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-10
 */

#pragma once
#include <iostream>

/**
 * @class Data
 * @brief Represents customer data
 */
class Data {
    public:
        Data();
        ~Data();
        int getCustomerNumber();
        void setCustomerNumber(int customerNumber);
        int getServiceTime();
        void setServiceTime(int serviceTime);
        int getTotalTime();
        void setTotalTime(int totalTime);
    private:
        static int instanceCount;
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
        QueueNode(Data *pData);
        ~QueueNode();
        Data *getData();
        void setData(Data *pData);
        QueueNode *getNext();
        void setNext(QueueNode *pNext);
    private:
        Data *pData;
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
        void enqueue(Data *pData);
        Data *dequeue();
        void printQueue();
    private:
        QueueNode *pHead;
        QueueNode *pTail;
};
