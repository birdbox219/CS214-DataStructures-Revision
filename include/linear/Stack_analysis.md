# Stack Analysis

## Time Complexity Summary

| Operation  | Best Case | Average Case | Worst Case | Space     |
|------------|-----------|--------------|------------|-----------|
| `push`     | $O(1)$    | $O(1)$*      | $O(n)$*    | $O(1)$    |
| `pop`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `top`      | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `size` / `empty` | $O(1)$ | $O(1)$    | $O(1)$     | $O(1)$    |
| `clear`    | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `contains` | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |

$n$ = number of elements. \*Amortized $O(1)$ for `push`; $O(n)$ when a resize occurs.

---

## Properties

A **Stack** is a **LIFO** (Last-In-First-Out) data structure. This implementation uses a dynamic array internally:

- The **top** of the stack is `arr[sz - 1]` (the last occupied slot)
- `push` appends to the end; `pop` removes from the end
- When the underlying array is full, `resize` doubles capacity
- Only the top element is directly accessible; no indexed access is provided
- The interface enforces LIFO discipline — users cannot insert or remove from arbitrary positions

---

## Per-Operation Proofs

### `push` — $O(1)$ amortized

**Algorithm:** If `sz == cap`, double capacity by allocating a new array, copying all elements, and deleting the old one. Then place `val` at `arr[sz]` and increment `sz`.

**Proof:** Same amortized argument as `ArrayList::pushBack`. Most pushes are $O(1)$ — a single store and increment. A resize copies all $n$ elements ($O(n)$), but doubling ensures each element is copied at most once per growth phase. Charging $O(1)$ extra per push amortizes the resize cost. Worst-case individual push (triggering resize): $O(n)$. Average across all pushes: $O(1)$.

### `pop` — $O(1)$

**Algorithm:** Decrement `sz`. No reallocation, no shifting.

**Proof:** $T(n) = O(1)$. Throws `std::out_of_range` if empty. Capacity is never shrunk.

### `top` — $O(1)$

**Algorithm:** Return `arr[sz - 1]`.

**Proof:** Direct array index. $T(n) = O(1)$. Throws if empty.

### `size` / `empty` — $O(1)$

Return the cached `sz` field.

### `clear` — $O(1)$

Set `sz = 0`. Does not deallocate memory.

### `contains` — $O(n)$

Linear scan from index 0 to $sz-1$. Worst case: value missing or at the bottom of the stack.

---

## Memory

| Aspect               | Array-based Stack          | Linked-list Stack          |
|----------------------|----------------------------|----------------------------|
| Per-element overhead | 0                          | 1 pointer (~8 bytes)       |
| Total for $n$ items  | $n \times T$ + slack       | $n \times (T + 8)$         |
| Allocation           | Single contiguous block    | Per node (fragmented)      |
| Cache locality       | Excellent                  | Poor                       |
| Capacity slack       | $(cap - sz) \times T$      | None (exact per push)      |

---

## Comparison: Array-based Stack vs Linked-list Stack

| Aspect              | Array Stack                  | Linked-list Stack            |
|---------------------|------------------------------|------------------------------|
| `push`              | $O(1)$ amortized             | $O(1)$                       |
| `pop`               | $O(1)$                       | $O(1)$                       |
| `top`               | $O(1)$                       | $O(1)$                       |
| Memory per element  | Lower (contiguous, no ptrs)  | Higher (per-node pointer)    |
| Allocation cost     | Rare (resize only)           | Every push (`new`)           |
| Cache locality      | Excellent                    | Poor                         |
| Space overhead      | Slack (unused capacity)      | None (exact allocation)      |
| Reverse traversal   | Not applicable               | Not applicable               |
| Random access       | Not exposed                  | Not exposed                  |

Both achieve the same asymptotic complexity for all stack operations. The array-based stack is generally faster in practice due to:

- **Fewer allocations** — `resize` happens $O(\log n)$ times vs $n$ `new` calls
- **Cache efficiency** — contiguous memory means sequential accesses hit the cache
- **Lower per-element overhead** — no pointer storage

The linked-list stack eliminates capacity slack and has perfectly predictable per-push cost (no occasional resize), making it suitable for real-time systems where worst-case latency must be bounded.

---

## Example Trace

### Push sequence: `push(1), push(2), push(3)`

```
Initial: cap=0, sz=0, arr=[]

push(1):  sz == cap → resize() → cap=1
          arr = [1]                     cap=1, sz=1  top=1

push(2):  sz == cap → resize() → cap=2
          copy: [1] → [1, _]
          arr = [1, 2]                  cap=2, sz=2  top=2

push(3):  sz == cap → resize() → cap=4
          copy: [1, 2] → [1, 2, _, _]
          arr = [1, 2, 3, _]            cap=4, sz=3  top=3
```

### Pop sequence: `pop(), pop()`

```
Start:  arr = [1, 2, 3, _]            cap=4, sz=3  top=3
pop():  --sz                           cap=4, sz=2  top=2
pop():  --sz                           cap=4, sz=1  top=1
```

### LIFO order demonstrated

```
push(10), push(20), push(30)
top()  → 30
pop()  → removes 30
top()  → 20
pop()  → removes 20
top()  → 10
```
