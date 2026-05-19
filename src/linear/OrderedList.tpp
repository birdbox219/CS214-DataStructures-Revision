#include "linear/OrderedList.h"
#include <algorithm>
#include <stdexcept>

// === Resize helper ==========================================================

template <typename T>
void OrderedList<T>::resize(int newCap) {
    T* newArr = new T[newCap];
    for (int i = 0; i < sz; ++i)
        newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// === binarySearch ===========================================================

template <typename T>
int OrderedList<T>::binarySearch(const T& val) const {
    auto it = std::lower_bound(arr, arr + sz, val);
    int pos = static_cast<int>(it - arr);
    if (pos < sz && arr[pos] == val)
        return pos;
    return -(pos + 1);
}

// === Big Three ==============================================================

template <typename T>
OrderedList<T>::OrderedList()
    : arr(nullptr), cap(0), sz(0) {}

template <typename T>
OrderedList<T>::~OrderedList() {
    delete[] arr;
}

template <typename T>
OrderedList<T>::OrderedList(const OrderedList& other)
    : arr(nullptr), cap(other.cap), sz(other.sz)
{
    if (cap > 0) {
        arr = new T[cap];
        for (int i = 0; i < sz; ++i)
            arr[i] = other.arr[i];
    }
}

template <typename T>
OrderedList<T>& OrderedList<T>::operator=(const OrderedList& other) {
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

// === Insert =================================================================

template <typename T>
void OrderedList<T>::insert(const T& val) {
    if (sz == cap)
        resize(cap == 0 ? 1 : cap * 2);
    int pos = binarySearch(val);
    if (pos < 0)
        pos = -(pos + 1);
    for (int i = sz; i > pos; --i)
        arr[i] = arr[i - 1];
    arr[pos] = val;
    ++sz;
}

// === Remove =================================================================

template <typename T>
bool OrderedList<T>::remove(const T& val) {
    int pos = binarySearch(val);
    if (pos < 0)
        return false;
    for (int i = pos; i < sz - 1; ++i)
        arr[i] = arr[i + 1];
    --sz;
    return true;
}

template <typename T>
T OrderedList<T>::removeAt(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("OrderedList::removeAt(): index out of range");
    T val = arr[index];
    for (int i = index; i < sz - 1; ++i)
        arr[i] = arr[i + 1];
    --sz;
    return val;
}

// === Get ====================================================================

template <typename T>
T& OrderedList<T>::get(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("OrderedList::get(): index out of range");
    return arr[index];
}

template <typename T>
const T& OrderedList<T>::get(int index) const {
    if (index < 0 || index >= sz)
        throw std::out_of_range("OrderedList::get(): index out of range");
    return arr[index];
}

// === Find / Contains ========================================================

template <typename T>
int OrderedList<T>::find(const T& val) const {
    int pos = binarySearch(val);
    return pos >= 0 ? pos : -1;
}

template <typename T>
bool OrderedList<T>::contains(const T& val) const {
    return binarySearch(val) >= 0;
}

// === Size / Capacity / Empty / Clear ========================================

template <typename T>
int OrderedList<T>::size() const {
    return sz;
}

template <typename T>
int OrderedList<T>::capacity() const {
    return cap;
}

template <typename T>
bool OrderedList<T>::empty() const {
    return sz == 0;
}

template <typename T>
void OrderedList<T>::clear() {
    sz = 0;
}
