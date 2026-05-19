#pragma once

#include <functional>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data;
    Compare comp;

    static int parent(int i);
    static int left(int i);
    static int right(int i);
    void heapifyUp(int i);
    void heapifyDown(int i);
    void build(const std::vector<T>& v);

public:
    Heap();
    explicit Heap(const Compare& comp);
    Heap(const std::vector<T>& v);

    void push(const T& value);
    void pop();
    const T& top() const;

    int size() const;
    bool empty() const;
    void clear();
};

#include "tree/Heap.tpp"
