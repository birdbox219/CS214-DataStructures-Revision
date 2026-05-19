#pragma once

#include <functional>
#include "tree/Heap.h"

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
    Heap<T, Compare> heap;

public:
    PriorityQueue();
    explicit PriorityQueue(const Compare& comp);

    void push(const T& val);
    void pop();
    const T& top() const;

    int size() const;
    bool empty() const;
    void clear();
};

#include "linear/PriorityQueue.tpp"
