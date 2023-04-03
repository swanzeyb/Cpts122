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
class List {
private:
    Node<T>* head;
    int size;

public:
    // Constructor
    List() : head(nullptr), size(0) {}

    // Destructor
    ~List() {
        clear();
    }

    // Copy constructor
    List(const List<T>& other);

    // Copy assignment operator
    List<T>& operator=(const List<T>& other);

    // Move constructor
    List(List<T>&& other);

    // Move assignment operator
    List<T>& operator=(List<T>&& other);

    // Member functions
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
            cout << "Empty List." << endl;
        } else {
            Node<T>* current = head;
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    };
};
