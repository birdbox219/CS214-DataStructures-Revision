#pragma once

#include <stdexcept>

template <typename T>
class OrderedList {
private:
    T* arr;
    int cap;
    int sz;

    void resize(int newCap);
    int binarySearch(const T& val) const;

public:
    OrderedList();
    ~OrderedList();
    OrderedList(const OrderedList& other);
    OrderedList& operator=(const OrderedList& other);

    void insert(const T& val);
    bool remove(const T& val);
    T removeAt(int index);

    T& get(int index);
    const T& get(int index) const;

    int find(const T& val) const;
    bool contains(const T& val) const;

    int size() const;
    int capacity() const;
    bool empty() const;
    void clear();
};

#include "linear/OrderedList.tpp"
