/**
 * @file LinkedList.h
 * @brief A generic LinkedList implementation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() {
        clear();
    }

    /**
     * @brief Checks if the LinkedList is empty
     * 
     * @return true 
     * @return false 
     */
    bool isEmpty() const {
        return head == nullptr;
    };

    /**
     * @brief Get the count of elements
     * 
     * @return int 
     */
    int getSize() const {
        return size;
    };

    /**
     * @brief Inserts an element at the front
     * 
     * @param data 
     */
    void insertAtFront(const T& data) {
        head = new Node(data, head);
        size++;
    };

    /**
     * @brief Inserts an element at the back
     * 
     * @param data 
     */
    void insertAtBack(const T& data) {
        if (isEmpty()) {
            insertAtFront(data);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(data);
            size++;
        }
    };

    /**
     * @brief Finds and removes an element
     * 
     * @param data 
     * @return true 
     * @return false 
     */
    bool remove(const T& data) {
        if (isEmpty()) {
            return false;
        } else {
            Node* current = head;

            while (current->next != nullptr && current->next->data != data) {
                current = current->next;
            }
            
            if (current->next == nullptr) {
                return false;
            } else {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }
        }
    };

    /**
     * @brief Finds an element
     * 
     * @param data 
     * @return Node* 
     */
    Node* find(const T& data) const {
        if (isEmpty()) {
            return nullptr;
        } else {
            Node* current = head;
            while (current != nullptr && current->data != data) {
                current = current->next;
            }
            return current;
        }
    };

    /**
     * @brief Empties the list and deletes all nodes
     * 
     */
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
            size--;
        }
        head = nullptr;
    };

    /**
     * @brief Prints each element
     * 
     */
    void print() const {
        if (isEmpty()) {
            cout << "Empty LinkedList." << endl;
        } else {
            Node* current = head;
            while (current != nullptr) {
                cout << current->data;
                current = current->next;
            }
            cout << endl;
        }
    };

    /**
     * @brief Get the head of llist
     * 
     * @return Node* 
     */
    Node* getHead() const {
        return head;
    };
};
