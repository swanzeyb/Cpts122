/**
 * @file Stack.h
 * @brief A generic Stack implementation
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @date 2023-04-03
 */

#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;

template <typename T>
class Stack {
public:
    Stack() {}
    ~Stack() {}

    /**
     * @brief Push an item onto the stack
     * 
     * @param item 
     */
    void push(const T& item) {
        stack.push_back(item);
    };

    /**
     * @brief Pop an item off the stack
     * 
     */
    void pop() {
        stack.pop_back();
    };

    /**
     * @brief Peek the item at top of stack
     * 
     * @return T& 
     */
    T& peek() {
        return stack.back();
    };

    /**
     * @brief Check if the stack is empty
     * 
     * @return true 
     * @return false 
     */
    bool isEmpty() const {
        return stack.empty();
    };

    /**
     * @brief Get the count of items in the stack
     * 
     * @return int 
     */
    int size() const {
        return stack.size();
    };

private:
    vector<T> stack;
};
