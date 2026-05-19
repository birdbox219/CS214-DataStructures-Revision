#include "linear/Queue.h"
#include <stdexcept>

// === Big Three ==============================================================

template <typename T>
Queue<T>::Queue()
    : head(nullptr), tail(nullptr), sz(0) {}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
Queue<T>::Queue(const Queue& other)
    : head(nullptr), tail(nullptr), sz(0)
{
    for (QueueNode<T>* cur = other.head; cur != nullptr; cur = cur->next)
        push(cur->data);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        for (QueueNode<T>* cur = other.head; cur != nullptr; cur = cur->next)
            push(cur->data);
    }
    return *this;
}

// === Push / Pop / Front / Back ==============================================

template <typename T>
void Queue<T>::push(const T& val) {
    QueueNode<T>* newNode = new QueueNode<T>(val);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++sz;
}

template <typename T>
void Queue<T>::pop() {
    if (empty())
        throw std::out_of_range("Queue::pop(): queue is empty");
    QueueNode<T>* oldHead = head;
    head = head->next;
    delete oldHead;
    if (head == nullptr)
        tail = nullptr;
    --sz;
}

template <typename T>
T& Queue<T>::front() {
    if (empty())
        throw std::out_of_range("Queue::front(): queue is empty");
    return head->data;
}

template <typename T>
const T& Queue<T>::front() const {
    if (empty())
        throw std::out_of_range("Queue::front(): queue is empty");
    return head->data;
}

template <typename T>
T& Queue<T>::back() {
    if (empty())
        throw std::out_of_range("Queue::back(): queue is empty");
    return tail->data;
}

template <typename T>
const T& Queue<T>::back() const {
    if (empty())
        throw std::out_of_range("Queue::back(): queue is empty");
    return tail->data;
}

// === Size / Empty / Clear ===================================================

template <typename T>
int Queue<T>::size() const {
    return sz;
}

template <typename T>
bool Queue<T>::empty() const {
    return sz == 0;
}

template <typename T>
void Queue<T>::clear() {
    while (head != nullptr) {
        QueueNode<T>* cur = head;
        head = head->next;
        delete cur;
    }
    tail = nullptr;
    sz = 0;
}

// === Contains ===============================================================

template <typename T>
bool Queue<T>::contains(const T& val) const {
    for (QueueNode<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == val)
            return true;
    }
    return false;
}
