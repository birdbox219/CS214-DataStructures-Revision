#pragma once

#include <stdexcept>

template <typename T>
class CircularQueue {
private:
    T* arr;
    int cap;
    int head;
    int tail;
    int sz;

    void resize(int newCap);

public:
    CircularQueue(int initialCap = 8);
    ~CircularQueue();
    CircularQueue(const CircularQueue& other);
    CircularQueue& operator=(const CircularQueue& other);

    void push(const T& val);
    void pop();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    int size() const;
    int capacity() const;
    bool empty() const;
    bool full() const;
    void clear();
};

#include "linear/CircularQueue.tpp"
