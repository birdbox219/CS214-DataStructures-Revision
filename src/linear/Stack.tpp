#include "linear/Stack.h"
#include <stdexcept>

// === Resize helper ==========================================================

template <typename T>
void Stack<T>::resize() {
    int newCap = cap == 0 ? 1 : cap * 2;
    T* newArr = new T[newCap];
    for (int i = 0; i < sz; ++i)
        newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// === Big Three ==============================================================

template <typename T>
Stack<T>::Stack()
    : arr(nullptr), cap(0), sz(0) {}

template <typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template <typename T>
Stack<T>::Stack(const Stack& other)
    : arr(nullptr), cap(other.cap), sz(other.sz)
{
    if (cap > 0) {
        arr = new T[cap];
        for (int i = 0; i < sz; ++i)
            arr[i] = other.arr[i];
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        delete[] arr;
        cap = other.cap;
        sz = other.sz;
        arr = nullptr;
        if (cap > 0) {
            arr = new T[cap];
            for (int i = 0; i < sz; ++i)
                arr[i] = other.arr[i];
        }
    }
    return *this;
}

// === Push / Pop / Top =======================================================

template <typename T>
void Stack<T>::push(const T& val) {
    if (sz == cap)
        resize();
    arr[sz++] = val;
}

template <typename T>
void Stack<T>::pop() {
    if (empty())
        throw std::out_of_range("Stack::pop(): stack is empty");
    --sz;
}

template <typename T>
T& Stack<T>::top() {
    if (empty())
        throw std::out_of_range("Stack::top(): stack is empty");
    return arr[sz - 1];
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty())
        throw std::out_of_range("Stack::top(): stack is empty");
    return arr[sz - 1];
}

// === Size / Empty / Clear ===================================================

template <typename T>
int Stack<T>::size() const {
    return sz;
}

template <typename T>
bool Stack<T>::empty() const {
    return sz == 0;
}

template <typename T>
void Stack<T>::clear() {
    sz = 0;
}

// === Contains ===============================================================

template <typename T>
bool Stack<T>::contains(const T& val) const {
    for (int i = 0; i < sz; ++i) {
        if (arr[i] == val)
            return true;
    }
    return false;
}
