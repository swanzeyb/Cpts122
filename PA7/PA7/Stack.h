
#pragma once

#include <vector>

template <typename T>
class Stack {
public:
    Stack() {}
    ~Stack() {}

    void push(const T& item) {
        stack.push_back(item);
    };

    void pop() {
        stack.pop_back();
    };

    T& peek() {
        return stack.back();
    };

    bool isEmpty() const {
        return stack.empty();
    };

    int size() const {
        return stack.size();
    };

private:
    std::vector<T> stack;
};
