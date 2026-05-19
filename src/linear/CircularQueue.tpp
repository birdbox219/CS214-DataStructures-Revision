#include "linear/CircularQueue.h"
#include <stdexcept>

// === Resize helper ==========================================================

template <typename T>
void CircularQueue<T>::resize(int newCap) {
    T* newArr = new T[newCap];
    for (int i = 0; i < sz; ++i)
        newArr[i] = arr[(head + i) % cap];
    delete[] arr;
    arr = newArr;
    cap = newCap;
    head = 0;
    tail = sz;
}

// === Big Three ==============================================================

template <typename T>
CircularQueue<T>::CircularQueue(int initialCap)
    : cap(initialCap), head(0), tail(0), sz(0)
{
    arr = new T[cap];
}

template <typename T>
CircularQueue<T>::~CircularQueue() {
    delete[] arr;
}

template <typename T>
CircularQueue<T>::CircularQueue(const CircularQueue& other)
    : arr(nullptr), cap(other.cap), head(0), tail(other.sz), sz(other.sz)
{
    if (cap > 0) {
        arr = new T[cap];
        for (int i = 0; i < sz; ++i)
            arr[i] = other.arr[(other.head + i) % other.cap];
    }
}

template <typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& other) {
    if (this != &other) {
        delete[] arr;
        cap = other.cap;
        head = 0;
        tail = other.sz;
        sz = other.sz;
        arr = nullptr;
        if (cap > 0) {
            arr = new T[cap];
            for (int i = 0; i < sz; ++i)
                arr[i] = other.arr[(other.head + i) % other.cap];
        }
    }
    return *this;
}

// === Push / Pop =============================================================

template <typename T>
void CircularQueue<T>::push(const T& val) {
    if (sz == cap)
        resize(cap == 0 ? 1 : cap * 2);
    arr[tail] = val;
    tail = (tail + 1) % cap;
    ++sz;
}

template <typename T>
void CircularQueue<T>::pop() {
    if (empty())
        throw std::out_of_range("CircularQueue::pop(): queue is empty");
    head = (head + 1) % cap;
    --sz;
}

// === Front / Back ===========================================================

template <typename T>
T& CircularQueue<T>::front() {
    if (empty())
        throw std::out_of_range("CircularQueue::front(): queue is empty");
    return arr[head];
}

template <typename T>
const T& CircularQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("CircularQueue::front(): queue is empty");
    return arr[head];
}

template <typename T>
T& CircularQueue<T>::back() {
    if (empty())
        throw std::out_of_range("CircularQueue::back(): queue is empty");
    return arr[(tail - 1 + cap) % cap];
}

template <typename T>
const T& CircularQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("CircularQueue::back(): queue is empty");
    return arr[(tail - 1 + cap) % cap];
}

// === Size / Capacity / Empty / Full / Clear =================================

template <typename T>
int CircularQueue<T>::size() const {
    return sz;
}

template <typename T>
int CircularQueue<T>::capacity() const {
    return cap;
}

template <typename T>
bool CircularQueue<T>::empty() const {
    return sz == 0;
}

template <typename T>
bool CircularQueue<T>::full() const {
    return sz == cap;
}

template <typename T>
void CircularQueue<T>::clear() {
    head = 0;
    tail = 0;
    sz = 0;
}
