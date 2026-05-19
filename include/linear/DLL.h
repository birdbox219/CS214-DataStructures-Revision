#pragma once

template <typename T>
struct DLLNode {
    T data;
    DLLNode<T>* prev;
    DLLNode<T>* next;

    DLLNode(const T& data, DLLNode<T>* prev = nullptr, DLLNode<T>* next = nullptr)
        : data(data), prev(prev), next(next) {}
};

template <typename T>
class DLL {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int sz;

    DLLNode<T>* nodeAt(int index) const;

public:
    DLL();
    ~DLL();
    DLL(const DLL& other);
    DLL& operator=(const DLL& other);

    void pushFront(const T& value);
    void pushBack(const T& value);

    void popFront();
    void popBack();

    void insert(int index, const T& value);
    T remove(int index);

    T& get(int index);
    const T& get(int index) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    int size() const;
    bool empty() const;
    void clear();

    bool contains(const T& value) const;
    void reverse();
};

#include "linear/DLL.tpp"
