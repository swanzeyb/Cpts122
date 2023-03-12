/**
 * @file Queue.cpp
 * @brief A queue implementation for the line simulation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-03-10
 */

#include "Queue.h"

// Initialize the static instance count
int Customer::expressCount = 0;
int Customer::regularCount = 0;

/**
 * @brief Construct a new Customer object
 * This represents a customer in the queue.
 * @return Customer
 */
Customer::Customer(LaneType laneType) {
    this->laneType = laneType;

    // Keep track of the number of customers in each lane
    if (laneType == EXPRESS) {
        this->customerNumber = Customer::expressCount++;
    } else {
        this->customerNumber = Customer::regularCount++;
    }
    
    this->serviceTime = 0;
    this->totalTime = 0;
}

Customer::~Customer() {
}

/**
 * @brief Get the Customer Number
 * 
 * @return int 
 */
int Customer::getCustomerNumber() {
    return this->customerNumber;
}

/**
 * @brief Set the Customer Number
 * 
 * @param int customerNumber 
 */
void Customer::setCustomerNumber(int customerNumber) {
    this->customerNumber = customerNumber;
}

/**
 * @brief Get the length of serivce time
 * 
 * @return int 
 */
int Customer::getServiceTime() {
    return this->serviceTime;
}

/**
 * @brief Set the length of service time
 * 
 * @param int serviceTime 
 */
void Customer::setServiceTime(int serviceTime) {
    this->serviceTime = serviceTime;
}

/**
 * @brief Get the total time in the queue
 * 
 * @return int 
 */
int Customer::getTotalTime() {
    return this->totalTime;
}

/**
 * @brief Set the total time in the queue
 * 
 * @param int totalTime 
 */
void Customer::setTotalTime(int totalTime) {
    this->totalTime = totalTime;
}

/**
 * @brief Construct a new Queue Node object
 * This node is used inside the queue, it stores the customer data
 * and a pointer to the next node in the queue.
 * @param pData Customer data
 * @return QueueNode
 */
QueueNode::QueueNode(Customer *pData) {
    this->pData = pData;
    this->pNext = nullptr;
}

QueueNode::~QueueNode() {
}

/**
 * @brief Get the Customer object
 * 
 * @return Customer*
 */
Customer *QueueNode::getData() {
    return this->pData;
}

/**
 * @brief Set the Customer object
 * 
 * @param Customer *pData 
 */
void QueueNode::setData(Customer *pData) {
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
void Queue::enqueue(Customer *pData) {
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
 * @return Customer* Customer of removed customer
 */
Customer *Queue::dequeue() {
    // If the queue is empty, return nullptr
    if (this->pHead == nullptr) {
        return nullptr;
    }

    // Otherwise, get the data from the head of the queue
    Customer *pData = this->pHead->getData();

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

Customer *Queue::peek() {
    // If the queue is empty, return nullptr
    if (this->pHead == nullptr) {
        return nullptr;
    }

    // Otherwise, get the data from the head of the queue
    Customer *pData = this->pHead->getData();

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

        // Count the length
        int length = 0;
        while (pCurr != nullptr) {
            length++;
            // std::cout << "Customer #" << pCurr->getData()->getCustomerNumber() << std::endl;
            pCurr = pCurr->getNext();
        }
        std::cout
            << length
            << " customers in line."
            << std::endl;
    }
}

/**
 * @brief Reset the number of customers in each lane
 */
void Customer::resetCount() {
    Customer::expressCount = 0;
    Customer::regularCount = 0;
}

/**
 * @brief Check if the queue is empty
 * 
 * @return bool is empty
 */
bool Queue::isEmpty() {
    return this->pHead == nullptr;
}
