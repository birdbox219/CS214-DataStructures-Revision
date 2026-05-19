#include "linear/ArrayList.h"
#include <stdexcept>

// === Resize helper ==========================================================

template <typename T>
void ArrayList<T>::resize(int newCap) {
    T* newArr = new T[newCap];
    for (int i = 0; i < sz; ++i)
        newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

// === Big Three ==============================================================

template <typename T>
ArrayList<T>::ArrayList()
    : arr(nullptr), cap(0), sz(0) {}

template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] arr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& other)
    : arr(nullptr), cap(other.cap), sz(other.sz)
{
    if (cap > 0) {
        arr = new T[cap];
        for (int i = 0; i < sz; ++i)
            arr[i] = other.arr[i];
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
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

// === Push / Pop =============================================================

template <typename T>
void ArrayList<T>::pushBack(const T& val) {
    if (sz == cap)
        reserve(cap == 0 ? 1 : cap * 2);
    arr[sz++] = val;
}

template <typename T>
void ArrayList<T>::popBack() {
    if (empty())
        throw std::out_of_range("ArrayList::popBack(): list is empty");
    --sz;
}

template <typename T>
void ArrayList<T>::pushFront(const T& val) {
    if (sz == cap)
        reserve(cap == 0 ? 1 : cap * 2);
    for (int i = sz; i > 0; --i)
        arr[i] = arr[i - 1];
    arr[0] = val;
    ++sz;
}

template <typename T>
void ArrayList<T>::popFront() {
    if (empty())
        throw std::out_of_range("ArrayList::popFront(): list is empty");
    for (int i = 0; i < sz - 1; ++i)
        arr[i] = arr[i + 1];
    --sz;
}

// === Insert / Remove ========================================================

template <typename T>
void ArrayList<T>::insert(int index, const T& val) {
    if (index < 0 || index > sz)
        throw std::out_of_range("ArrayList::insert(): index out of range");
    if (sz == cap)
        reserve(cap == 0 ? 1 : cap * 2);
    for (int i = sz; i > index; --i)
        arr[i] = arr[i - 1];
    arr[index] = val;
    ++sz;
}

template <typename T>
T ArrayList<T>::remove(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("ArrayList::remove(): index out of range");
    T val = arr[index];
    for (int i = index; i < sz - 1; ++i)
        arr[i] = arr[i + 1];
    --sz;
    return val;
}

// === Get / Operator[] =======================================================

template <typename T>
T& ArrayList<T>::get(int index) {
    if (index < 0 || index >= sz)
        throw std::out_of_range("ArrayList::get(): index out of range");
    return arr[index];
}

template <typename T>
const T& ArrayList<T>::get(int index) const {
    if (index < 0 || index >= sz)
        throw std::out_of_range("ArrayList::get(): index out of range");
    return arr[index];
}

template <typename T>
T& ArrayList<T>::operator[](int index) {
    return arr[index];
}

template <typename T>
const T& ArrayList<T>::operator[](int index) const {
    return arr[index];
}

// === Size / Capacity / Empty / Clear ========================================

template <typename T>
int ArrayList<T>::size() const {
    return sz;
}

template <typename T>
int ArrayList<T>::capacity() const {
    return cap;
}

template <typename T>
bool ArrayList<T>::empty() const {
    return sz == 0;
}

template <typename T>
void ArrayList<T>::clear() {
    sz = 0;
}

// === Contains / Reserve =====================================================

template <typename T>
bool ArrayList<T>::contains(const T& val) const {
    for (int i = 0; i < sz; ++i) {
        if (arr[i] == val)
            return true;
    }
    return false;
}

template <typename T>
void ArrayList<T>::reserve(int newCap) {
    if (newCap > cap)
        resize(newCap);
}
