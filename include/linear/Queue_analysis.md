# Queue Analysis

## Time Complexity Summary

| Operation  | Best Case | Average Case | Worst Case | Space     |
|------------|-----------|--------------|------------|-----------|
| `push`     | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `pop`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `front`    | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `back`     | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `size` / `empty` | $O(1)$ | $O(1)$    | $O(1)$     | $O(1)$    |
| `clear`    | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `contains` | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |

$n$ = number of elements.

---

## Properties

A **Queue** is a **FIFO** (First-In-First-Out) data structure. This implementation uses a singly linked list with both head and tail pointers:

- **head** — points to the front of the queue (dequeue side)
- **tail** — points to the back of the queue (enqueue side)
- `push` appends at the tail ($O(1)$ via tail pointer)
- `pop` removes from the head ($O(1)$ via head pointer)
- Each node is individually heap-allocated with `new`/`delete`

---

## Per-Operation Proofs

### `push` — $O(1)$

**Algorithm:** Create a new node. If the queue is empty, set both `head` and `tail` to the new node. Otherwise, link `tail->next` to the new node and advance `tail`.

**Proof:** All operations are pointer assignments — no traversal. $T(n) = O(1)$.

### `pop` — $O(1)$

**Algorithm:** Save `head`, advance `head` to `head->next`, delete the old head. If `head` becomes `nullptr`, also set `tail = nullptr`.

**Proof:** All operations are $O(1)$ pointer reassignments and one `delete`. Throws `std::out_of_range` if empty.

### `front` — $O(1)$

**Algorithm:** Return `head->data`.

**Proof:** Direct pointer dereference. $T(n) = O(1)$. Throws if empty.

### `back` — $O(1)$

**Algorithm:** Return `tail->data`.

**Proof:** The `tail` pointer gives direct access to the last node. $T(n) = O(1)$. Throws if empty.

### `size` / `empty` — $O(1)$

Return the cached `sz` field.

### `clear` — $O(n)$

**Algorithm:** Walk from `head` to `nullptr`, deleting each node.

**Proof:** Visits $n$ nodes exactly once. Each `delete` is $O(1)$. Total: $O(n)$.

### `contains` — $O(n)$

Linear scan from `head` to `tail`. Worst case: value not found or at the tail, visiting all $n$ nodes.

---

## Memory

| Aspect               | Linked Queue                | Circular Array Queue     |
|----------------------|-----------------------------|--------------------------|
| Per-element overhead | 1 pointer (~8 bytes)        | 0                        |
| Total for $n$ items  | $n \times (T + 8)$          | $n \times T$ + slack     |
| Allocation           | Per node (fragmented)       | Single contiguous block  |
| Capacity slack       | None (exact per push)       | $(cap - sz) \times T$    |
| Cache locality       | Poor (pointer chasing)      | Excellent                |

---

## Comparison: Linked Queue vs Circular Array Queue

| Aspect              | Linked Queue                 | Circular Array Queue        |
|---------------------|-------------------------------|-----------------------------|
| `push`              | $O(1)$                        | $O(1)$ amortized            |
| `pop`               | $O(1)$                        | $O(1)$                      |
| `front` / `back`    | $O(1)$                        | $O(1)$                      |
| Memory per element  | Higher (per-node pointer)     | Lower (contiguous, no ptrs) |
| Allocation cost     | Every push (`new`)            | Rare (resize only)          |
| Cache locality      | Poor                          | Excellent                   |
| Space overhead      | None (exact allocation)       | Slack (unused capacity)     |
| Worst-case latency  | Predictable (no resize)       | Occasional resize $O(n)$    |
| Random access       | Not exposed                   | Not exposed                 |

Both achieve $O(1)$ asymptotic complexity for queue operations. The linked queue has predictable per-operation cost (no resize pauses), making it suitable for real-time systems. The circular array queue is faster in practice due to contiguous memory, fewer allocations, and better cache utilization.

A **circular array queue** uses a fixed-size or growable array with wrap-around indices (`frontIdx`, `backIdx` modulo capacity). When the array is full, it must resize and copy. The linked queue avoids this entirely by allocating per-node.

---

## Example Trace

### Push sequence: `push(10), push(20), push(30)`

```
Initial: head=nullptr, tail=nullptr, sz=0

push(10):  new node[10]
           head = tail = [10]             sz=1

push(20):  new node[20]
           tail->next = [20], tail = [20] sz=2
           head → [10] → [20] ← tail

push(30):  new node[30]
           tail->next = [30], tail = [30] sz=3
           head → [10] → [20] → [30] ← tail
```

### Pop sequence: `pop(), pop()`

```
Start: head → [10] → [20] → [30] ← tail   sz=3
pop():  delete [10], head = [20]           sz=2
pop():  delete [20], head = [30]           sz=1
        head → [30] ← tail
```

### FIFO order demonstrated

```
push(1), push(2), push(3)
front() → 1
pop()   → removes 1
front() → 2
pop()   → removes 2
front() → 3
```

Empty queue:
```
pop():  head == nullptr → throw std::out_of_range
front(): head == nullptr → throw std::out_of_range
back():  tail == nullptr → throw std::out_of_range
```
