#pragma once

#include <stdexcept>

template <typename T>
class ArrayList {
private:
    T* arr;
    int cap;
    int sz;

    void resize(int newCap);

public:
    ArrayList();
    ~ArrayList();
    ArrayList(const ArrayList& other);
    ArrayList& operator=(const ArrayList& other);

    void pushBack(const T& val);
    void popBack();
    void pushFront(const T& val);
    void popFront();
    void insert(int index, const T& val);
    T remove(int index);

    T& get(int index);
    const T& get(int index) const;

    T& operator[](int index);
    const T& operator[](int index) const;

    int size() const;
    int capacity() const;
    bool empty() const;
    void clear();
    bool contains(const T& val) const;
    void reserve(int newCap);
};

#include "linear/ArrayList.tpp"
