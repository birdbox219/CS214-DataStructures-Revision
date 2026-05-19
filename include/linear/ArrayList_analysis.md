# ArrayList Analysis

## Time Complexity Summary

| Operation       | Best Case | Average Case | Worst Case | Space     |
|-----------------|-----------|--------------|------------|-----------|
| `pushBack`      | $O(1)$    | $O(1)$*      | $O(n)$*    | $O(1)$    |
| `popBack`       | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `pushFront`     | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `popFront`      | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `insert`        | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `remove`        | $O(n)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `get` / `operator[]` | $O(1)$ | $O(1)$    | $O(1)$     | $O(1)$    |
| `size` / `capacity` / `empty` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `clear`         | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `contains`      | $O(1)$    | $O(n)$       | $O(n)$     | $O(1)$    |
| `reserve`       | $O(1)$    | $O(n)$       | $O(n)$     | $O(n)$    |

$n$ = number of elements. \*Amortized $O(1)$ for `pushBack`; $O(n)$ when a resize occurs.

---

## Properties

An **ArrayList** is a dynamic array — a contiguous block of memory that grows automatically when full.

- Elements are stored in a **contiguous** memory block (`arr`)
- `cap` tracks the allocated capacity
- `sz` tracks the number of elements actually in use
- On `pushBack` when `sz == cap`, the array **doubles** in capacity (via `reserve`)
- Only the public `reserve` and push/pop methods resize the array; `clear` leaves capacity unchanged
- Random access is $O(1)$ — the defining advantage over linked structures

---

## Per-Operation Proofs

### `pushBack` — $O(1)$ amortized

**Algorithm:** If `sz == cap`, call `reserve(cap * 2)` to double capacity. Then place `val` at `arr[sz]` and increment `sz`.

**Proof:** Most insertions are $O(1)$ — just a store and increment. When a resize occurs, all $n$ existing elements must be copied to new memory: $O(n)$. By the **banker's accounting** argument, if we charge 3 "tokens" per `pushBack` (one for the store, two saved for future copying), the $n$ copies during a resize are paid for by the $n$ tokens previously saved. Each element is copied at most once per resize, and resizing happens only when the array doubles, so the amortized cost is $O(1)$. Worst-case (the insertion that triggers a resize) is $O(n)$.

### `popBack` — $O(1)$

**Algorithm:** Decrement `sz`. No reallocation, no shifting.

**Proof:** $T(n) = O(1)$. Note: capacity is **never** shrunk.

### `pushFront` — $O(n)$

**Algorithm:** If full, reserve double capacity. Shift all elements one position to the right (`arr[i] = arr[i-1]` for $i = sz$ down to $1$), then place `val` at `arr[0]`.

**Proof:** Shifting $n$ elements requires $n$ assignments. $T(n) = O(n)$. If a resize is also needed, total is $O(n)$.

### `popFront` — $O(n)$

**Algorithm:** Shift all elements one position to the left (`arr[i] = arr[i+1]` for $i = 0$ to $sz-2$), then decrement `sz`.

**Proof:** $n-1$ elements are moved. $T(n) = O(n)$.

### `insert` — $O(n)$

**Algorithm:** Validate $0 \le index \le sz$. If full, reserve double capacity. Shift elements from $index$ rightward by one, then place `val` at `arr[index]`.

**Proof:** In the worst case ($index = 0$), all $n$ elements shift right: $O(n)$. The best case ($index = sz$) requires no shift but is still the `pushBack` path: $O(1)$ amortized.

### `remove` — $O(n)$

**Algorithm:** Validate $0 \le index < sz$. Save `arr[index]`, shift elements from $index+1$ leftward by one, decrement `sz`, return the saved value.

**Proof:** Worst case ($index = 0$) shifts $n-1$ elements: $O(n)$. Best case ($index = sz-1$) shifts zero: $O(1)$.

### `get` / `operator[]` — $O(1)$

**Algorithm:** Bounds-checked `get` validates then returns `arr[index]`; unchecked `operator[]` returns directly.

**Proof:** Contiguous memory + pointer arithmetic gives direct address computation: `*(arr + index)`. $T(n) = O(1)$. This is the key advantage of array-based structures.

### `size` / `capacity` / `empty` — $O(1)$

Return the cached `sz` / `cap` fields.

### `clear` — $O(1)$

Set `sz = 0`. Does not deallocate memory (`cap` unchanged).

### `contains` — $O(n)$

Linear scan from index 0 to $sz-1$. Worst case: value not found or at the last position.

### `reserve` — $O(n)$

**Algorithm:** If `newCap <= cap`, do nothing. Otherwise allocate `new T[newCap]`, copy all $sz$ elements, delete old array.

**Proof:** Copies $n$ elements: $O(n)$. Only grows; never shrinks.

---

## Memory

| Aspect               | ArrayList                     | Singly Linked List          |
|----------------------|-------------------------------|-----------------------------|
| Per-element overhead | 0                             | 1 pointer (~8 bytes)        |
| Total for $n$ items  | $n \times T$ + slack          | $n \times (T + 8)$          |
| Allocation           | Single contiguous block       | Per node (fragmented)       |
| Slack                | $(cap - sz) \times T$ wasted  | 0 wasted (exact allocation) |
| Cache locality       | Excellent (sequential memory) | Poor (pointer chasing)      |

---

## Comparison: ArrayList vs Singly Linked List

| Operation       | ArrayList            | Singly Linked List   |
|-----------------|----------------------|----------------------|
| `pushBack`      | $O(1)$ amortized     | $O(1)$               |
| `popBack`       | $O(1)$               | $O(n)$               |
| `pushFront`     | $O(n)$               | $O(1)$               |
| `popFront`      | $O(n)$               | $O(1)$               |
| `get(i)`        | $O(1)$               | $O(n)$               |
| `insert(i)`     | $O(n)$               | $O(n)$               |
| `remove(i)`     | $O(n)$               | $O(n)$               |
| Memory overhead | Low (contiguous)     | High (per-node ptr)   |
| Cache locality  | Excellent            | Poor                  |

ArrayLists excel at **random access and back operations**. Linked lists excel at **frequent front insertions/removals**.

---

## Example Trace

### Insert sequence: `pushBack(1), pushBack(2), pushFront(0), insert(2, 5)`

```
Initial: cap=0, sz=0, arr=[]

Step 1: pushBack(1)
    sz == cap → reserve(1)
    arr = [1]                     cap=1, sz=1

Step 2: pushBack(2)
    sz == cap → reserve(2)
    copy: [1] → [1, _]
    arr = [1, 2]                  cap=2, sz=2

Step 3: pushFront(0)
    sz == cap → reserve(4)
    copy: [1, 2] → [1, 2, _, _]
    shift right: [_, 1, 2, _] → [0, 1, 2, _]
    arr = [0, 1, 2, _]            cap=4, sz=3

Step 4: insert(2, 5)
    shift right from index 2: [0, 1, _, 2] → [0, 1, 5, 2]
    arr = [0, 1, 5, 2]            cap=4, sz=4
```

### Remove sequence: `popFront(), popBack()`

```
Start:  arr = [0, 1, 5, 2]       cap=4, sz=4
popFront(): shift left: [1, 5, 2, _]   arr = [1, 5, 2, _]   cap=4, sz=3
popBack():  decrement sz               arr = [1, 5, _, _]   cap=4, sz=2
```

### Access pattern

```
get(1): returns arr[1] = 5        O(1) — direct index
operator[0]: returns arr[0] = 1   O(1) — no bounds check
```
