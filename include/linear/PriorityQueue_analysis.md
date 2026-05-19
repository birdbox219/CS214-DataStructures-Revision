# PriorityQueue Analysis

## Time Complexity Summary

| Operation  | Best / Average / Worst | Space     |
|------------|------------------------|-----------|
| `push`     | $O(\log n)$            | $O(1)$    |
| `pop`      | $O(\log n)$            | $O(1)$    |
| `top`      | $O(1)$                 | $O(1)$    |
| `size`     | $O(1)$                 | $O(1)$    |
| `empty`    | $O(1)$                 | $O(1)$    |
| `clear`    | $O(n)$                 | $O(1)$    |

$n$ = number of elements.

---

## Properties

A **PriorityQueue** is a container that provides access to the **highest-priority** element (by default, the largest, when using `std::less<T>` — corresponding to a max-heap).

This implementation is a thin **adapter** (wrapper) around the existing `Heap` data structure:

- All operations delegate directly to the `Heap<T, Compare>` member
- No Rule of Three needed — `Heap` stores elements in a `std::vector`, which handles its own copying
- The `Compare` template parameter (default `std::less<T>`) determines the priority order:
  - `std::less<T>` → max-heap → `top()` returns the **largest** element
  - `std::greater<T>` → min-heap → `top()` returns the **smallest** element

---

## Per-Operation Proofs

### `push` — $O(\log n)$

**Algorithm:** Delegate to `heap.push(val)`, which appends to the vector and sifts up.

**Proof:** The heap's sift-up traverses at most $h = \lfloor \log_2 n \rfloor$ levels. Each step does $O(1)$ work (one comparison + one swap). Total: $O(\log n)$. See `Heap::push` analysis for full proof.

### `pop` — $O(\log n)$

**Algorithm:** Delegate to `heap.pop()`, which replaces the root with the last element, removes the last, and sifts down.

**Proof:** Sift-down traverses $O(\log n)$ levels with $O(1)$ work per level. Total: $O(\log n)$. Throws `std::runtime_error` if empty (propagated from `Heap::pop()`).

### `top` — $O(1)$

**Algorithm:** Return `heap.top()` — i.e., `data[0]`.

**Proof:** Direct array lookup into the heap's internal vector. $T(n) = O(1)$. Throws if empty.

### `size` / `empty` — $O(1)$

Delegate to `std::vector::size()` / `std::vector::empty()` — both $O(1)$.

### `clear` — $O(n)$

Delegate to `std::vector::clear()`, which destroys all $n$ elements.

---

## Memory

| Aspect               | PriorityQueue (Heap)    | Unsorted Array         | Sorted Array           |
|----------------------|-------------------------|------------------------|------------------------|
| Per-element overhead | 0 (uses `std::vector`)  | 0                      | 0                      |
| Allocation           | Contiguous block         | Contiguous block       | Contiguous block       |
| `push`               | $O(\log n)$             | $O(1)$ amortized       | $O(n)$                 |
| `pop`                | $O(\log n)$             | $O(n)$                 | $O(1)$                 |
| `top`                | $O(1)$                  | $O(n)$                 | $O(1)$                 |

---

## Comparison: Priority Queue Implementations

| Aspect               | Heap-based (this)       | Unsorted Array         | Sorted Array           |
|----------------------|-------------------------|------------------------|------------------------|
| `push`               | $O(\log n)$             | $O(1)$ amortized       | $O(n)$ (shift)         |
| `pop`                | $O(\log n)$             | $O(n)$ (scan + swap)   | $O(1)$                 |
| `top`                | $O(1)$                  | $O(n)$ (linear scan)   | $O(1)$                 |
| Memory overhead      | Low                     | Low                    | Low                    |
| Implementation       | Moderate                | Trivial                | Trivial                |

**Unsorted array priority queue:**
- `push` is fast ($O(1)$ amortized) — just append
- `pop` is slow ($O(n)$) — must scan to find the max/min, then swap with the last element
- `top` is slow ($O(n)$) — must scan to find the max/min
- Best when pushes vastly outnumber pops

**Sorted array priority queue:**
- `push` is slow ($O(n)$) — must shift elements to maintain sorted order
- `pop` is fast ($O(1)$) — remove from the end
- `top` is fast ($O(1)$) — read the last element
- Best when pops vastly outnumber pushes

**Heap-based priority queue (this implementation):**
- Both `push` and `pop` are $O(\log n)$ — balanced for general use
- No operation is worse than $O(\log n)$
- The best general-purpose choice when push/pop frequency is unknown or roughly equal

---

## Example Trace

### Max-priority queue (default `std::less`): `push(3), push(7), push(1), push(9), push(5)`

```
Internal heap state after each push (max-heap):

push(3):  [3]
push(7):  [7, 3]           heapifyUp(1): 7 > 3 → swap
push(1):  [7, 3, 1]        heapifyUp(2): 1 < 3 → no swap
push(9):  [9, 7, 1, 3]     heapifyUp(3): 9 > 3 → swap → [9, 7, 1, 3]
                             heapifyUp(1): 9 > 7 → swap → [9, 7, 1, 3]
push(5):  [9, 7, 1, 3, 5]  heapifyUp(4): 5 < 7 → no swap
```

### Pop sequence: `pop() × 3`

```
Start:  [9, 7, 5, 3, 1]  (after heapify adjustments)

pop():  root=9 → [1, 7, 5, 3] → heapifyDown → [7, 3, 5, 1]
pop():  root=7 → [1, 3, 5]    → heapifyDown → [5, 3, 1]
pop():  root=5 → [1, 3]       → heapifyDown → [3, 1]
```

### Min-priority queue (`std::greater<int>`)

```
push(3), push(7), push(1), push(9), push(5):

push(3):  [3]
push(7):  [3, 7]            heapifyUp(1): 7 > 3 → no swap (greater: swap when parent > child)
push(1):  [1, 7, 3]         heapifyUp(2): 1 < 3 → swap → [1, 7, 3]
                             heapifyUp(0): 1 < 3 → swap → [1, 7, 3]
push(9):  [1, 7, 3, 9]      heapifyUp(3): 9 > 7 → no swap
push(5):  [1, 5, 3, 9, 7]   heapifyUp(4): 7 > 5 → swap → [1, 5, 3, 9, 7]

top() → 1  (smallest element)
```

### Priority order

```
PriorityQueue<int> pq;                     // max-priority
pq.push(30); pq.push(10); pq.push(20);
top() → 30  (largest)
pop() → removes 30
top() → 20
pop() → removes 20
top() → 10
```
