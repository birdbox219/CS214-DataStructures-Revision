#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& data, Node<T>* next = nullptr)
        : data(data), next(next) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int sz;

    Node<T>* nodeAt(int index) const;

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

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

#include "linear/LinkedList.tpp"
