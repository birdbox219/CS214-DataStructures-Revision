#include <stdexcept>

template <typename T>
DLL<T>::DLL() : head(nullptr), tail(nullptr), sz(0) {}

template <typename T>
DLL<T>::~DLL() {
    clear();
}

template <typename T>
DLL<T>::DLL(const DLL& other) : head(nullptr), tail(nullptr), sz(0) {
    DLLNode<T>* cur = other.head;
    while (cur) {
        pushBack(cur->data);
        cur = cur->next;
    }
}

template <typename T>
DLL<T>& DLL<T>::operator=(const DLL& other) {
    if (this != &other) {
        clear();
        DLLNode<T>* cur = other.head;
        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}

template <typename T>
DLLNode<T>* DLL<T>::nodeAt(int index) const {
    if (index < 0 || index >= sz) return nullptr;
    if (index < sz / 2) {
        DLLNode<T>* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur;
    } else {
        DLLNode<T>* cur = tail;
        for (int i = sz - 1; i > index; --i) cur = cur->prev;
        return cur;
    }
}

template <typename T>
void DLL<T>::pushFront(const T& value) {
    DLLNode<T>* newNode = new DLLNode<T>(value, nullptr, head);
    if (head) head->prev = newNode;
    else tail = newNode;
    head = newNode;
    ++sz;
}

template <typename T>
void DLL<T>::pushBack(const T& value) {
    DLLNode<T>* newNode = new DLLNode<T>(value, tail, nullptr);
    if (tail) tail->next = newNode;
    else head = newNode;
    tail = newNode;
    ++sz;
}

template <typename T>
void DLL<T>::popFront() {
    if (empty()) throw std::out_of_range("DLL is empty");
    DLLNode<T>* oldHead = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete oldHead;
    --sz;
}

template <typename T>
void DLL<T>::popBack() {
    if (empty()) throw std::out_of_range("DLL is empty");
    DLLNode<T>* oldTail = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete oldTail;
    --sz;
}

template <typename T>
void DLL<T>::insert(int index, const T& value) {
    if (index < 0 || index > sz) throw std::out_of_range("Index out of range");
    if (index == 0) { pushFront(value); return; }
    if (index == sz) { pushBack(value); return; }
    DLLNode<T>* at = nodeAt(index);
    DLLNode<T>* prevNode = at->prev;
    DLLNode<T>* newNode = new DLLNode<T>(value, prevNode, at);
    prevNode->next = newNode;
    at->prev = newNode;
    ++sz;
}

template <typename T>
T DLL<T>::remove(int index) {
    if (index < 0 || index >= sz) throw std::out_of_range("Index out of range");
    if (index == 0) { T val = front(); popFront(); return val; }
    if (index == sz - 1) { T val = back(); popBack(); return val; }
    DLLNode<T>* at = nodeAt(index);
    T val = at->data;
    at->prev->next = at->next;
    at->next->prev = at->prev;
    delete at;
    --sz;
    return val;
}

template <typename T>
T& DLL<T>::get(int index) {
    if (index < 0 || index >= sz) throw std::out_of_range("Index out of range");
    return nodeAt(index)->data;
}

template <typename T>
const T& DLL<T>::get(int index) const {
    if (index < 0 || index >= sz) throw std::out_of_range("Index out of range");
    return nodeAt(index)->data;
}

template <typename T>
T& DLL<T>::front() {
    if (empty()) throw std::out_of_range("DLL is empty");
    return head->data;
}

template <typename T>
const T& DLL<T>::front() const {
    if (empty()) throw std::out_of_range("DLL is empty");
    return head->data;
}

template <typename T>
T& DLL<T>::back() {
    if (empty()) throw std::out_of_range("DLL is empty");
    return tail->data;
}

template <typename T>
const T& DLL<T>::back() const {
    if (empty()) throw std::out_of_range("DLL is empty");
    return tail->data;
}

template <typename T>
int DLL<T>::size() const { return sz; }

template <typename T>
bool DLL<T>::empty() const { return sz == 0; }

template <typename T>
void DLL<T>::clear() {
    while (head) {
        DLLNode<T>* cur = head;
        head = head->next;
        delete cur;
    }
    tail = nullptr;
    sz = 0;
}

template <typename T>
bool DLL<T>::contains(const T& value) const {
    DLLNode<T>* cur = head;
    while (cur) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

template <typename T>
void DLL<T>::reverse() {
    DLLNode<T>* cur = head;
    while (cur) {
        DLLNode<T>* temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    DLLNode<T>* temp = head;
    head = tail;
    tail = temp;
}
