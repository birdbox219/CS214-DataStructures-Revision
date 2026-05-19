#include "linear/PriorityQueue.h"
#include <stdexcept>

// === Constructors ===========================================================

template <typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue()
    : heap() {}

template <typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue(const Compare& comp)
    : heap(comp) {}

// === Public API =============================================================

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& val) {
    heap.push(val);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
    heap.pop();
}

template <typename T, typename Compare>
const T& PriorityQueue<T, Compare>::top() const {
    return heap.top();
}

template <typename T, typename Compare>
int PriorityQueue<T, Compare>::size() const {
    return heap.size();
}

template <typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
    return heap.empty();
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::clear() {
    heap.clear();
}
