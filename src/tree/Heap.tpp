#include "tree/Heap.h"
#include <algorithm>
#include <stdexcept>

// === Index helpers =========================================================

template <typename T, typename Compare>
int Heap<T, Compare>::parent(int i) {
    return (i - 1) / 2;
}

template <typename T, typename Compare>
int Heap<T, Compare>::left(int i) {
    return 2 * i + 1;
}

template <typename T, typename Compare>
int Heap<T, Compare>::right(int i) {
    return 2 * i + 2;
}

// === Constructors ==========================================================

template <typename T, typename Compare>
Heap<T, Compare>::Heap()
    : comp(Compare()) {}

template <typename T, typename Compare>
Heap<T, Compare>::Heap(const Compare& comp)
    : comp(comp) {}

template <typename T, typename Compare>
Heap<T, Compare>::Heap(const std::vector<T>& v)
    : comp(Compare())
{
    build(v);
}

// === Build =================================================================

template <typename T, typename Compare>
void Heap<T, Compare>::build(const std::vector<T>& v) {
    data = v;

    for (int i = (int)data.size() / 2 - 1; i >= 0; --i)
        heapifyDown(i);
}

// === Heapify operations ====================================================

template <typename T, typename Compare>
void Heap<T, Compare>::heapifyUp(int i) {
    while (i > 0 && comp(data[parent(i)], data[i])) {
        std::swap(data[parent(i)], data[i]);
        i = parent(i);
    }
}

template <typename T, typename Compare>
void Heap<T, Compare>::heapifyDown(int i) {
    int n = (int)data.size();

    while (true) {
        int top = i;
        int l = left(i);
        int r = right(i);

        if (l < n && comp(data[top], data[l]))
            top = l;

        if (r < n && comp(data[top], data[r]))
            top = r;

        if (top == i) break;

        std::swap(data[i], data[top]);
        i = top;
    }
}

// === Public API ============================================================

template <typename T, typename Compare>
void Heap<T, Compare>::push(const T& value) {
    data.push_back(value);
    heapifyUp((int)data.size() - 1);
}

template <typename T, typename Compare>
void Heap<T, Compare>::pop() {
    if (data.empty())
        throw std::runtime_error("Heap::pop(): heap is empty");

    data[0] = data.back();
    data.pop_back();

    if (!data.empty())
        heapifyDown(0);
}

template <typename T, typename Compare>
const T& Heap<T, Compare>::top() const {
    if (data.empty())
        throw std::runtime_error("Heap::top(): heap is empty");

    return data[0];
}

template <typename T, typename Compare>
int Heap<T, Compare>::size() const {
    return (int)data.size();
}

template <typename T, typename Compare>
bool Heap<T, Compare>::empty() const {
    return data.empty();
}

template <typename T, typename Compare>
void Heap<T, Compare>::clear() {
    data.clear();
}
