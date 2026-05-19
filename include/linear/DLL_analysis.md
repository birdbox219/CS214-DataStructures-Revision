# DLL (Doubly Linked List) Analysis

## Time Complexity Summary

| Operation       | Best Case | Average Case | Worst Case | Space     |
|-----------------|-----------|--------------|------------|-----------|
| `pushFront`     | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `pushBack`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `popFront`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `popBack`       | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `insert`        | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `remove`        | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `get`           | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `front` / `back` | $O(1)$  | $O(1)$       | $O(1)$     | $O(1)$    |
| `size` / `empty` | $O(1)$  | $O(1)$       | $O(1)$     | $O(1)$    |
| `clear`         | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `contains`      | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `reverse`       | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |

$n$ = number of nodes.

---

## Properties

A doubly linked list is a linear data structure where each element (node) stores:
- A **data** value
- A **pointer** to the previous node (`prev`)
- A **pointer** to the next node (`next`)

The list is identified by two pointers:
- `head` — first node
- `tail` — last node

Bidirectional linking enables $O(1)$ `popBack` and reverse traversal from `tail`. The cost is one extra pointer per node vs a singly linked list.

---

## Comparison: Singly vs Doubly Linked List

| Feature           | Singly Linked List | Doubly Linked List     |
|-------------------|--------------------|------------------------|
| Pointers per node | 1 (`next`)         | 2 (`prev`, `next`)     |
| `popBack`         | $O(n)$             | $O(1)$                 |
| `reverse`         | $O(n)$             | $O(n)$ (simpler swap)  |
| Memory overhead   | $n \times (T + 8)$ | $n \times (T + 16)$    |
| Backward traversal | No                 | Yes                    |
| `get` from tail   | No                 | Yes (nearer end chosen)|

---

## Per-Operation Proofs

### `pushFront` — $O(1)$

**Algorithm:** Create a new node whose `next` is `head` and `prev` is `nullptr`. If the list is non-empty, set `head->prev = newNode`. Update `head = newNode`. If the list was empty, also set `tail = newNode`.

**Proof:** Pure pointer reassignments — no traversal. $T(n) = O(1)$.

### `pushBack` — $O(1)$

**Algorithm:** Symmetric to `pushFront`. Create a new node whose `prev` is `tail` and `next` is `nullptr`. If non-empty, set `tail->next = newNode`. Update `tail = newNode`.

**Proof:** The `tail` pointer gives direct access. $T(n) = O(1)$.

### `popFront` — $O(1)$

**Algorithm:** Save `head`, advance `head` to `head->next`, set `head->prev = nullptr` (if non-null). Delete old head. If the list becomes empty, set `tail = nullptr`.

**Proof:** All pointer operations cost $O(1)$.

### `popBack` — $O(1)$ (vs $O(n)$ in singly linked list)

**Algorithm:** Save `tail`, retreat `tail` to `tail->prev`, set `tail->next = nullptr` (if non-null). Delete old tail. If the list becomes empty, set `head = nullptr`.

**Proof:** The `prev` pointer on the last node directly gives the new tail — no traversal needed. This is the key advantage of a DLL over a singly linked list. $T(n) = O(1)$.

### `insert` — $O(n)$

**Algorithm:** Three cases:
1. Index 0 → `pushFront` ($O(1)$)
2. Index $n$ → `pushBack` ($O(1)$)
3. Middle → use `nodeAt(index)` to find the target node, then link a new node between `at->prev` and `at`

**Proof:** `nodeAt` may traverse from either `head` (if $index < n/2$) or `tail` (otherwise), visiting $\min(index, n-index)$ nodes. In the worst case this is $\lceil n/2 \rceil = O(n)$. Pointer rewiring is $O(1)$.

### `remove` — $O(n)$

**Algorithm:** Three cases:
1. Index 0 → `popFront` ($O(1)$)
2. Last index → `popBack` ($O(1)$)
3. Middle → `nodeAt(index)`, then rewire `at->prev->next = at->next` and `at->next->prev = at->prev`, delete `at`

**Proof:** Same traversal reasoning as `insert`. Finding the node via `nodeAt` costs $O(n)$ worst case. Deletion itself is $O(1)$.

### `get` — $O(n)$

**Algorithm:** Uses `nodeAt` which traverses from `head` if $index < n/2$, or from `tail` otherwise.

**Proof:** Half-range optimization halves the average constant but does not change the asymptotic bound: worst-case $index = n/2$ visits $\lfloor n/2 \rfloor = O(n)$ nodes.

### `front` / `back` — $O(1)$

Return `head->data` / `tail->data` directly.

### `size` / `empty` — $O(1)$

Use the cached `sz` counter.

### `clear` — $O(n)$

Iterate from `head`, deleting each node. Visits $n$ nodes exactly once.

### `contains` — $O(n)$

Linear search from `head` to `tail`. Worst case visits all $n$ nodes.

### `reverse` — $O(n)$

**Algorithm:** Swap `prev` and `next` for every node, then swap `head` and `tail`:

```
cur = head
while cur != nullptr:
    swap(cur->prev, cur->next)
    cur = cur->prev   // original next after swap
swap(head, tail)
```

**Proof:** Each node is visited exactly once, doing $O(1)$ pointer swaps per node. Total: $O(n)$.

---

## Memory

| Aspect               | Singly Linked List   | Doubly Linked List     | Dynamic Array         |
|----------------------|----------------------|------------------------|-----------------------|
| Per-element overhead | 1 pointer (~8 bytes) | 2 pointers (~16 bytes) | 0                     |
| Total for $n$ items  | $n \times (T + 8)$   | $n \times (T + 16)$    | $n \times T$ + slack  |
| Allocation           | Per node (fragmented)| Per node (fragmented)  | Contiguous block      |
| `popBack`            | $O(n)$               | $O(1)$                 | $O(1)$                |

---

## Comparison: DLL vs Dynamic Array

| Operation       | Doubly Linked List | Dynamic Array (std::vector) |
|-----------------|--------------------|------------------------------|
| `pushFront`     | $O(1)$             | $O(n)$                       |
| `pushBack`      | $O(1)$             | $O(1)$ amortized             |
| `popFront`      | $O(1)$             | $O(n)$                       |
| `popBack`       | $O(1)$             | $O(1)$                       |
| `get(i)`        | $O(n)$             | $O(1)$                       |
| `insert(i)`     | $O(n)$             | $O(n)$                       |
| `remove(i)`     | $O(n)$             | $O(n)$                       |
| Memory overhead | $2n$ pointers      | $0$                          |
| Cache locality  | Poor               | Excellent                    |

DLL excels at **front and back operations** both being $O(1)$. Arrays still win for random access.

---

## Example Trace

### Insert sequence: `pushBack(1), pushBack(2), pushFront(0), insert(2, 5)`

```
Step 1: pushBack(1)          head ↔ [1] ↔ tail
Step 2: pushBack(2)          head ↔ [1] ↔ [2] ↔ tail
Step 3: pushFront(0)         head ↔ [0] ↔ [1] ↔ [2] ↔ tail
Step 4: insert(2, 5)         head ↔ [0] ↔ [1] ↔ [5] ↔ [2] ↔ tail
```

### Remove sequence: `popFront(), popBack()`

```
Start:       head ↔ [0] ↔ [1] ↔ [5] ↔ [2] ↔ tail
popFront():  head ↔ [1] ↔ [5] ↔ [2] ↔ tail          (delete [0])
popBack():   head ↔ [1] ↔ [5] ↔ tail                (delete [2] via prev pointer — O(1))
```

### Reverse: `reverse()`

```
Before: head ↔ [1] ↔ [5] ↔ [2] ↔ tail
After:  head ↔ [2] ↔ [5] ↔ [1] ↔ tail
```

Step by step:
```
cur = head = [1]
Iter 1: swap([1].prev, [1].next) → prev=[5], next=null, move to [5]
Iter 2: swap([5].prev, [5].next) → prev=[2], next=[1],  move to [2]
Iter 3: swap([2].prev, [2].next) → prev=null, next=[5], move to null
swap(head, tail): head=[2], tail=[1]
```

---

## XOR Linked List — The Trick

A standard doubly linked list uses two pointers per node (`prev` and `next`), doubling the memory overhead of a singly linked list. The **XOR linked list** (also called a **memory-efficient doubly linked list**) stores a single pointer-sized field:

```
struct XORNode {
    T data;
    uintptr_t both;   // prev XOR next
};
```

where `both = (uintptr_t)prev ^ (uintptr_t)next`.

### Traversal

To traverse forward, you need the address of the **previous** node:

```
XORNode<T>* prev = nullptr;
XORNode<T>* cur = head;
while (cur) {
    // visit cur->data
    XORNode<T>* next = (XORNode<T>*)((uintptr_t)prev ^ cur->both);
    prev = cur;
    cur = next;
}
```

To traverse backward from `tail`:

```
XORNode<T>* next = nullptr;
XORNode<T>* cur = tail;
while (cur) {
    // visit cur->data
    XORNode<T>* prev = (XORNode<T>*)((uintptr_t)next ^ cur->both);
    next = cur;
    cur = prev;
}
```

**Why it works:** $A \oplus B \oplus A = B$. Given one of the two adjacent nodes, XORing it with the stored `both` field recovers the other.

### Memory Comparison

| Variant      | Per node   | Total for $n$ items     |
|--------------|------------|-------------------------|
| Singly       | 1 pointer  | $n \times (T + 8)$      |
| Doubly       | 2 pointers | $n \times (T + 16)$     |
| XOR          | 1 pointer  | $n \times (T + 8)$      |

The XOR list achieves doubly linked semantics using the **same per-node memory** as a singly linked list.

### Trade-offs vs Standard DLL

| Aspect            | Standard DLL        | XOR DLL                      |
|-------------------|---------------------|------------------------------|
| Memory per node   | 2 pointers          | 1 pointer (same as singly)   |
| Pointer arithmetic| Direct              | XOR required per step        |
| Insert/remove     | Any node accessible | Must know both neighbors     |
| Debugging         | Debugger-friendly   | Opaque `uintptr_t` value     |
| Compatibility     | Any C++ compiler    | `uintptr_t` + strict aliasing|
| Random deletion   | Trivial             | Impractical                  |
| Reverse traversal | Trivial             | Must start from `tail`       |

The XOR trick is primarily a **curiosity** in modern systems — memory is cheap, and the extra arithmetic, aliasing concerns, and debuggability loss rarely justify the space savings.
