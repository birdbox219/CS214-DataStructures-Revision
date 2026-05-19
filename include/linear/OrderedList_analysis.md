# OrderedList Analysis

## Time Complexity Summary

| Operation     | Best Case | Average Case | Worst Case | Space     |
|---------------|-----------|--------------|------------|-----------|
| `insert`      | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `remove`      | $O(1)$    | $O(\log n)$  | $O(n)$     | $O(1)$    |
| `removeAt`    | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `get`         | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `find`        | $O(1)$    | $O(\log n)$  | $O(\log n)$| $O(1)$    |
| `contains`    | $O(1)$    | $O(\log n)$  | $O(\log n)$| $O(1)$    |
| `size` / `capacity` / `empty` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `clear`       | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |

$n$ = number of elements.

---

## Properties

An **OrderedList** is a sorted dynamic array that maintains elements in ascending order using binary search for insertion and lookup.

- Elements are stored in a **contiguous** sorted block (`arr`)
- `cap` tracks allocated capacity; doubles when full
- `sz` tracks number of elements
- `binarySearch` uses `std::lower_bound` — returns index if found, or negative insertion point
- **No duplicates allowed** in the sense that `remove` removes only one occurrence, but duplicates can exist (insert will place equal elements after existing ones due to lower_bound inserting at first `>=`)
- Random access via `get` is $O(1)$
- Lookup is $O(\log n)$ via binary search — the defining advantage over unsorted ArrayList ($O(n)$)

---

## Per-Operation Proofs

### `insert` — $O(n)$

**Algorithm:** If full, double capacity. Binary search for insertion position $p$. Shift elements at $p \ldots sz-1$ right by one. Place `val` at $p$ and increment `sz`.

**Proof:** Binary search costs $O(\log n)$. Shifting $n - p$ elements takes $O(n)$ in the worst case ($p = 0$). The shifting dominates, so $T(n) = O(n)$. If a resize is also needed, copying $n$ elements is also $O(n)$, so total remains $O(n)$.

### `remove` — $O(\log n)$ average, $O(n)$ worst

**Algorithm:** Binary search for `val`. If found, shift elements left; decrement `sz`. Return whether found.

**Proof:** Binary search is $O(\log n)$. If found, shifting costs $O(n)$ in the worst case ($p = 0$), but $O(1)$ if $p = sz-1$. If not found (element absent), we exit after the search with no shifting: $O(\log n)$. Average case depends on whether the element is present.

### `removeAt` — $O(n)$

**Algorithm:** Bounds-check index. Save `arr[index]`, shift left, decrement `sz`, return value.

**Proof:** Identical to `remove` without the search. Shifting dominates: $T(n) = O(n)$.

### `find` — $O(\log n)$

**Algorithm:** Binary search. If result $\ge 0$, return it; otherwise return $-1$.

**Proof:** One binary search call: $T(n) = O(\log n)$.

### `contains` — $O(\log n)$

**Algorithm:** Binary search; check if result $\ge 0$.

**Proof:** Identical to `find` cost: $T(n) = O(\log n)$.

### `get` — $O(1)$

**Algorithm:** Bounds-check, return `arr[index]`.

**Proof:** Contiguous memory + pointer arithmetic: $T(n) = O(1)$.

### `size` / `capacity` / `empty` — $O(1)$

Return cached fields.

### `clear` — $O(1)$

Set `sz = 0`. Capacity unchanged.

---

## Memory

| Aspect               | OrderedList                   | Unsorted ArrayList            |
|----------------------|-------------------------------|-------------------------------|
| Per-element overhead | 0                             | 0                             |
| Total for $n$ items  | $n \times T$ + slack          | $n \times T$ + slack          |
| Allocation           | Single contiguous block       | Single contiguous block       |
| Slack                | $(cap - sz) \times T$ wasted  | $(cap - sz) \times T$ wasted  |
| Cache locality       | Excellent (sequential memory) | Excellent (sequential memory) |
| **Lookup cost**      | $O(\log n)$ binary search     | $O(n)$ linear scan            |

Memory layout is identical to ArrayList. The only additional cost is the invariant that elements remain sorted, which is maintained at insertion time.

---

## Comparison with alternatives

| Operation  | OrderedList        | ArrayList          | Balanced BST (e.g., `std::set`) |
|------------|--------------------|--------------------|---------------------------------|
| `insert`   | $O(n)$             | $O(1)$ amortized   | $O(\log n)$                     |
| `remove`   | $O(n)$             | $O(n)$             | $O(\log n)$                     |
| `find`     | $O(\log n)$        | $O(n)$             | $O(\log n)$                     |
| `get(i)`   | $O(1)$             | $O(1)$             | $O(n)$ (no random access)       |
| Memory     | Low, contiguous    | Low, contiguous    | High, per-node pointers         |
| Cache      | Excellent          | Excellent          | Poor (pointer chasing)          |

**When to use OrderedList:**
- Need sorted data with fast binary search ($O(\log n)$)
- Need $O(1)$ random access by index
- Insertions are infrequent relative to lookups

**When not to use:**
- Frequent insertions — $O(n)$ shift cost dominates
- Need $O(\log n)$ or better insertion — use a balanced BST instead

---

## Example Trace

### Insert sequence: `insert(3), insert(1), insert(4), insert(2)`

```
Initial: cap=0, sz=0, arr=[]

Step 1: insert(3)
    resize(1)
    binarySearch(3) → pos=0
    arr = [3]                     cap=1, sz=1

Step 2: insert(1)
    resize(2)
    binarySearch(1) → pos=0 (neg → pos=0)
    shift right from 0: [_, 3]
    arr = [1, 3]                  cap=2, sz=2

Step 3: insert(4)
    resize(4)
    binarySearch(4) → pos=2 (neg → pos=2)
    arr = [1, 3, 4, _]            cap=4, sz=3

Step 4: insert(2)
    binarySearch(2) → pos=1 (neg → pos=1)
    shift right from 1: [1, _, 3, 4]
    arr = [1, 2, 3, 4]            cap=4, sz=4
```

### Remove sequence: `remove(4), remove(1)`

```
Start:  arr = [1, 2, 3, 4]        cap=4, sz=4
remove(4): binarySearch → pos=3   shift none    arr = [1, 2, 3, _]   sz=3
remove(1): binarySearch → pos=0   shift [2,3]   arr = [2, 3, _, _]   sz=2
```

### Lookup

```
find(3): binarySearch → pos=1     returns 1
find(5): binarySearch → not found returns -1
get(0):  returns arr[0] = 2       O(1)
contains(3): binarySearch → found returns true
```
