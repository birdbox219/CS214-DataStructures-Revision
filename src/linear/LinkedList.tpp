#include "linear/LinkedList.h"
#include <stdexcept>

// === Node helper ===========================================================

template <typename T>
Node<T>* LinkedList<T>::nodeAt(int index) const {
    Node<T>* cur = head;
    for (int i = 0; i < index; ++i)
        cur = cur->next;
    return cur;
}

// === Big Three =============================================================

template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr), tail(nullptr), sz(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    : head(nullptr), tail(nullptr), sz(0)
{
    for (Node<T>* cur = other.head; cur != nullptr; cur = cur->next)
        pushBack(cur->data);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        for (Node<T>* cur = other.head; cur != nullptr; cur = cur->next)
            pushBack(cur->data);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// === Push ==================================================================

template <typename T>
void LinkedList<T>::pushFront(const T& value) {
    head = new Node<T>(value, head);
    if (tail == nullptr)
        tail = head;
    ++sz;
}

template <typename T>
void LinkedList<T>::pushBack(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++sz;
}

// === Pop ===================================================================

template <typename T>
void LinkedList<T>::popFront() {
    if (empty())
        throw std::runtime_error("LinkedList::popFront(): list is empty");

    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete temp;
    --sz;
}

template <typename T>
void LinkedList<T>::popBack() {
    if (empty())
        throw std::runtime_error("LinkedList::popBack(): list is empty");

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* cur = head;
        while (cur->next != tail)
            cur = cur->next;

        delete tail;
        tail = cur;
        tail->next = nullptr;
    }
    --sz;
}

// === Insert / Remove =======================================================

template <typename T>
void LinkedList<T>::insert(int index, const T& value) {
    if (index < 0 || index > sz)
        throw std::out_of_range("LinkedList::insert(): index out of range");

    if (index == 0) {
        pushFront(value);
    } else if (index == sz) {
        pushBack(value);
    } else {
        Node<T>* prev = nodeAt(index - 1);
        prev->next = new Node<T>(value, prev->next);
        ++sz;
    }
}

template <typename T>
T LinkedList<T>::remove(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("LinkedList::remove(): index out of range");

    if (index == 0) {
        T val = head->data;
        popFront();
        return val;
    }

    Node<T>* prev = nodeAt(index - 1);
    Node<T>* target = prev->next;
    T val = target->data;

    prev->next = target->next;
    if (target == tail)
        tail = prev;

    delete target;
    --sz;
    return val;
}

// === Get / Front / Back ====================================================

template <typename T>
T& LinkedList<T>::get(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("LinkedList::get(): index out of range");

    return nodeAt(index)->data;
}

template <typename T>
const T& LinkedList<T>::get(int index) const {
    if (index < 0 || index >= sz)
        throw std::out_of_range("LinkedList::get(): index out of range");

    return nodeAt(index)->data;
}

template <typename T>
T& LinkedList<T>::front() {
    if (empty())
        throw std::runtime_error("LinkedList::front(): list is empty");

    return head->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    if (empty())
        throw std::runtime_error("LinkedList::front(): list is empty");

    return head->data;
}

template <typename T>
T& LinkedList<T>::back() {
    if (empty())
        throw std::runtime_error("LinkedList::back(): list is empty");

    return tail->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    if (empty())
        throw std::runtime_error("LinkedList::back(): list is empty");

    return tail->data;
}

// === Size / Empty / Clear ==================================================

template <typename T>
int LinkedList<T>::size() const {
    return sz;
}

template <typename T>
bool LinkedList<T>::empty() const {
    return sz == 0;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    sz = 0;
}

// === Contains / Reverse ====================================================

template <typename T>
bool LinkedList<T>::contains(const T& value) const {
    for (Node<T>* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == value)
            return true;
    }
    return false;
}

template <typename T>
void LinkedList<T>::reverse() {
    Node<T>* prev = nullptr;
    Node<T>* cur = head;
    tail = head;

    while (cur != nullptr) {
        Node<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head = prev;
}
