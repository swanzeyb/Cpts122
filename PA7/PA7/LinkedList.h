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
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& data, Node<T>* next = nullptr) : data(data), next(next) {}
};

template <typename T>
class LinkedList {
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
        head = new Node<T>(data, head);
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
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node<T>(data);
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
            Node<T>* current = head;

            while (current->next != nullptr && current->next->data != data) {
                current = current->next;
            }
            
            if (current->next == nullptr) {
                return false;
            } else {
                Node<T>* temp = current->next;
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
     * @return Node<T>* 
     */
    Node<T>* find(const T& data) const {
        if (isEmpty()) {
            return nullptr;
        } else {
            Node<T>* current = head;
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
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
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
            Node<T>* current = head;
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
     * @return Node<T>* 
     */
    Node<T>* getHead() const {
        return head;
    };

private:
    Node<T>* head;
    int size;
};
