#pragma once

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* arr;
    int cap;
    int sz;

    void resize();

public:
    Stack();
    ~Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);

    void push(const T& val);
    void pop();
    T& top();
    const T& top() const;

    int size() const;
    bool empty() const;
    void clear();
    bool contains(const T& val) const;
};

#include "linear/Stack.tpp"
