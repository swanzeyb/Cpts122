
#pragma once

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

template <typename T>
class Node {
public:
    const T& data;
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
    LinkedList(const LinkedList<T>& other);
    LinkedList(LinkedList<T>&& other);

    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other);

    bool isEmpty() const {
        return head == nullptr;
    };

    int getSize() const {
        return size;
    };

    void insertAtFront(const T& data) {
        head = new Node<T>(data, head);
        size++;
    };

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

    void clear() {
        while (!isEmpty()) {
            remove(head->data);
        }
    };

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

private:
    Node<T>* head;
    int size;
};
