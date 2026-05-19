#pragma once

#include <stdexcept>

template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;

    QueueNode(const T& data, QueueNode<T>* next = nullptr)
        : data(data), next(next) {}
};

template <typename T>
class Queue {
private:
    QueueNode<T>* head;
    QueueNode<T>* tail;
    int sz;

public:
    Queue();
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    void push(const T& val);
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    int size() const;
    bool empty() const;
    void clear();
    bool contains(const T& val) const;
};

#include "linear/Queue.tpp"
