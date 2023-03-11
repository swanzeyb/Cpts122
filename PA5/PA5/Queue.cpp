/**
 * @file Queue.h
 * @brief A queue implementation for the line simulation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-10
 */

#include "Queue.h"

// Initialize the static instance count
int Data::instanceCount = 0;

/**
 * @brief Construct a new Data object
 * 
 * @return Data
 */
Data::Data() {
    this->customerNumber = Data::instanceCount++;
    this->serviceTime = 0;
    this->totalTime = 0;
}

Data::~Data() {
}

/**
 * @brief Get the Customer Number
 * 
 * @return int 
 */
int Data::getCustomerNumber() {
    return this->customerNumber;
}

/**
 * @brief Set the Customer Number
 * 
 * @param int customerNumber 
 */
void Data::setCustomerNumber(int customerNumber) {
    this->customerNumber = customerNumber;
}

/**
 * @brief Get the length of serivce time
 * 
 * @return int 
 */
int Data::getServiceTime() {
    return this->serviceTime;
}

/**
 * @brief Set the length of service time
 * 
 * @param int serviceTime 
 */
void Data::setServiceTime(int serviceTime) {
    this->serviceTime = serviceTime;
}

/**
 * @brief Get the total time in the queue
 * 
 * @return int 
 */
int Data::getTotalTime() {
    return this->totalTime;
}

/**
 * @brief Set the total time in the queue
 * 
 * @param int totalTime 
 */
void Data::setTotalTime(int totalTime) {
    this->totalTime = totalTime;
}

/**
 * @brief Construct a new Queue Node object
 * This node is used inside the queue, it stores the customer data
 * and a pointer to the next node in the queue.
 * @param pData Customer data
 * @return QueueNode
 */
QueueNode::QueueNode(Data *pData) {
    this->pData = pData;
    this->pNext = nullptr;
}

QueueNode::~QueueNode() {
}

/**
 * @brief Get the Data object
 * 
 * @return Data*
 */
Data *QueueNode::getData() {
    return this->pData;
}

/**
 * @brief Set the Data object
 * 
 * @param Data *pData 
 */
void QueueNode::setData(Data *pData) {
    this->pData = pData;
}

/**
 * @brief Get the Next node
 * 
 * @return QueueNode* 
 */
QueueNode *QueueNode::getNext() {
    return this->pNext;
}

/**
 * @brief Set the Next node
 * 
 * @param QueueNode *pNext 
 */
void QueueNode::setNext(QueueNode *pNext) {
    this->pNext = pNext;
}

/**
 * @brief Construct a new Queue object
 * This implements a fifo queue data structure using linked lists.
 * Each node in the queue represents a customer in line for checkout.
 * @return Queue
 */
Queue::Queue() {
    this->pHead = nullptr;
    this->pTail = nullptr;
}

Queue::~Queue() {
}

/**
 * @brief Add a new customer to the queue
 * 
 * @param pData Customer data
 */
void Queue::enqueue(Data *pData) {
    // Create a new list node
    QueueNode *pMem = new QueueNode(pData);

    // If the queue is empty, set the head and tail to the new node
    if (this->pHead == nullptr) {
        this->pHead = pMem;
        this->pTail = pMem;
    } else {
        // Otherwise, add the new node to the end of the queue
        this->pTail->setNext(pMem);
        this->pTail = pMem;
    }
}

/**
 * @brief Remove the leading customer from the queue
 * 
 * @return Data* Data of removed customer
 */
Data *Queue::dequeue() {
    // If the queue is empty, return nullptr
    if (this->pHead == nullptr) {
        return nullptr;
    }

    // Otherwise, get the data from the head of the queue
    Data *pData = this->pHead->getData();

    // Remove the head of the queue
    QueueNode *pTemp = this->pHead;
    this->pHead = this->pHead->getNext();
    delete pTemp;

    // If the queue is now empty, set the tail to nullptr
    if (this->pHead == nullptr) {
        this->pTail = nullptr;
    }

    // Return the data
    return pData;
}

/**
 * @brief Print the queue to the console
 * 
 */
void Queue::printQueue() {
    // If the queue is empty, print a message
    if (this->pHead == nullptr) {
        std::cout << "The checkout line is empty." << std::endl;
    } else {
        // Otherwise, print the queue
        QueueNode *pCurr = this->pHead;

        std::cout << "The checkout line queue:" << std::endl;
        while (pCurr != nullptr) {
            std::cout << "Customer #" << pCurr->getData()->getCustomerNumber() << std::endl;
            pCurr = pCurr->getNext();
        }
        // std::cout << std::endl;
    }
}
