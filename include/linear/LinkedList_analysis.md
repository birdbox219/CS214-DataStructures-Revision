# LinkedList Analysis

## Time Complexity Summary

| Operation       | Best Case | Average Case | Worst Case | Space     |
|-----------------|-----------|--------------|------------|-----------|
| `pushFront`     | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `pushBack`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `popFront`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `popBack`       | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
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

A singly linked list is a linear data structure where each element (node) stores:
- A **data** value
- A **pointer** to the next node

The list is identified by two pointers:
- `head` — first node
- `tail` — last node

Unlike arrays, elements are **not stored contiguously** in memory. Each node is dynamically allocated.

---

## Per-Operation Proofs

### `pushFront` — $O(1)$

**Algorithm:** Create a new node pointing to the current `head`, then update `head` to the new node. If the list was empty, also set `tail`.

**Proof:** All operations are pointer assignments — no traversal. $T(n) = O(1)$.

### `pushBack` — $O(1)$

**Algorithm:** Create a new node, link it after `tail`, then update `tail`.

**Proof:** The `tail` pointer gives direct access to the last node. No traversal needed. $T(n) = O(1)$.

### `popFront` — $O(1)$

**Algorithm:** Save `head`, advance `head` to `head->next`, delete the old head. If the list becomes empty, set `tail = nullptr`.

**Proof:** All operations are $O(1)$ pointer reassignments.

### `popBack` — $O(n)$

**Algorithm:** To remove the last node, we must find the node **before** `tail`. Since nodes only point forward, this requires traversing from `head` to the second-to-last node.

**Proof:** The traversal visits $n-1$ nodes in the worst case. Each step is $O(1)$. Total: $O(n)$.

### `insert` — $O(n)$

**Algorithm:** Three cases:
1. Index 0 → `pushFront` ($O(1)$)
2. Index $n$ → `pushBack` ($O(1)$)
3. Middle → traverse to node at $index-1$, then rewire pointers

**Proof:** Finding the insertion point via `nodeAt` traverses $index-1$ nodes: $O(index) = O(n)$ worst case.

### `remove` — $O(n)$

**Algorithm:** Same three-case logic as `insert`:
1. Index 0 → `popFront` ($O(1)$)
2. Last index → `popBack` ($O(n)$)
3. Middle → traverse to node at $index-1$, rewire around the target, delete

**Proof:** Finding the predecessor via `nodeAt` costs $O(n)$. Deletion itself is $O(1)$.

### `get` — $O(n)$

**Algorithm:** Traverse $index$ steps from `head`.

**Proof:** Uses `nodeAt` which walks $index$ nodes. In the worst case $index = n-1$, so $O(n)$. (Contrast with array $O(1)$ random access.)

### `front` / `back` — $O(1)$

Return `head->data` / `tail->data` directly. No traversal.

### `size` / `empty` — $O(1)$

Use the cached `sz` counter.

### `clear` — $O(n)$

Iterate from `head`, deleting each node in sequence. Visits $n$ nodes exactly once.

### `contains` — $O(n)$

Linear search from `head` to `tail$. Worst case: the value is missing or at the tail, visiting all $n$ nodes.

### `reverse` — $O(n)$

**Algorithm:** Three-pointer iterative reversal:
```
prev = nullptr, cur = head
while cur != nullptr:
    next = cur->next
    cur->next = prev
    prev = cur
    cur = next
head = prev
```

**Proof:** Each node is visited exactly once. The pointer rewiring per node is $O(1)$. Total: $O(n)$. After reversal, `tail` is set to the original `head`.

---

## Memory

| Aspect               | Linked List          | Dynamic Array         |
|----------------------|----------------------|-----------------------|
| Per-element overhead | 1 pointer (~8 bytes) | 0                     |
| Total for $n$ items  | $n \times (T + 8)$   | $n \times T$ + slack  |
| Allocation           | Per node (fragmented)| Contiguous block      |
| Insertion at front   | $O(1)$               | $O(n)$                |

---

## Comparison: Linked List vs Dynamic Array

| Operation       | Singly Linked List | Dynamic Array (std::vector) |
|-----------------|--------------------|------------------------------|
| `pushFront`     | $O(1)$             | $O(n)$                       |
| `pushBack`      | $O(1)$             | $O(1)$ amortized             |
| `popFront`      | $O(1)$             | $O(n)$                       |
| `popBack`       | $O(n)$             | $O(1)$                       |
| `get(i)`        | $O(n)$             | $O(1)$                       |
| `insert(i)`     | $O(n)$             | $O(n)$                       |
| `remove(i)`     | $O(n)$             | $O(n)$                       |
| Memory overhead | High (per-node ptr)| Low (contiguous)             |
| Cache locality  | Poor               | Excellent                    |

Linked lists excel at **frequent front insertions/removals**. Arrays excel at **random access** and **back operations**.

---

## Example Trace

### Insert sequence: `pushBack(1), pushBack(2), pushFront(0), insert(2, 5)`

```
Step 1: pushBack(1)          head → [1] ← tail
Step 2: pushBack(2)          head → [1] → [2] ← tail
Step 3: pushFront(0)         head → [0] → [1] → [2] ← tail
Step 4: insert(2, 5)         head → [0] → [1] → [5] → [2] ← tail
```

### Remove sequence: `popFront(), popBack()`

```
Start:  head → [0] → [1] → [5] → [2] ← tail
popFront():    head → [1] → [5] → [2] ← tail   (delete [0])
popBack():     head → [1] → [5] ← tail          (find predecessor of tail, delete [2])
```

### Reverse: `reverse()`

```
Before: head → [1] → [5] → [2] ← tail
After:  head → [2] → [5] → [1] ← tail
```

Step by step:
```
prev = nullptr, cur = head = [1]
Iteration 1: next = [5], [1].next = nullptr, prev = [1], cur = [5]
Iteration 2: next = [2], [5].next = [1],  prev = [5], cur = [2]
Iteration 3: next = nullptr, [2].next = [5], prev = [2], cur = nullptr
head = prev = [2]
tail was set to original head = [1]
```
