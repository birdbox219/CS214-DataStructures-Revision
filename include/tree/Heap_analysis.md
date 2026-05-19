# Heap Analysis

## Time Complexity Summary

| Operation  | Best / Average / Worst | Space     |
|------------|------------------------|-----------|
| `push`     | $O(\log n)$            | $O(1)$    |
| `pop`      | $O(\log n)$            | $O(1)$    |
| `top`      | $O(1)$                 | $O(1)$    |
| `size`     | $O(1)$                 | $O(1)$    |
| `empty`    | $O(1)$                 | $O(1)$    |
| `clear`    | $O(n)$                 | $O(1)$    |
| `build`    | $O(n)$                 | $O(n)$    |

$n$ = number of elements.

---

## Properties

A binary heap is a **complete binary tree** stored in an array that satisfies the **heap property**:

- **Max-heap** (default, `std::less<T>`): parent $\ge$ children. The largest element is at the root.
- **Min-heap** (`std::greater<T>`): parent $\le$ children. The smallest element is at the root.

**Array representation:** For a node at index $i$:
- Parent: $\lfloor (i-1)/2 \rfloor$
- Left child: $2i + 1$
- Right child: $2i + 2$

**Completeness:** All levels are filled except possibly the last, which is filled left to right. The array is always dense — no gaps.

---

## Per-Operation Proofs

### `push` — $O(\log n)$

**Algorithm:** Append the new value at the end, then sift it up.

```
push(9):
  [5, 3, 4]  →  [5, 3, 4, 9]  →  heapifyUp(3)
                                        compare(4, 9) → swap → [5, 9, 4, 3]
                                        compare(5, 9) → swap → [9, 5, 4, 3]
```

**Proof:** The worst-case path from leaf to root has length $h = \lfloor \log_2 n \rfloor$. Each sift step does $O(1)$ work (one comparison + one swap). Total: $O(\log n)$.

### `pop` — $O(\log n)$

**Algorithm:** Replace the root with the last element, remove the last, then sift down.

```
pop():
  [9, 5, 4, 3]  →  [3, 5, 4]  →  heapifyDown(0)
                                      compare(3, 5) → swap → [5, 3, 4]
                                      compare(5, 4) → skip
```

**Proof:** Replace root = $O(1)$. Sift down traverses one path of length $h = O(\log n)$. Each step does $O(1)$ work. Total: $O(\log n)$.

### `top` — $O(1)$

Returns `data[0]` — array lookup is constant time.

### `size` / `empty` — $O(1)$

Delegates to `std::vector::size()` / `std::vector::empty()` — both $O(1)$.

### `clear` — $O(n)$

Delegates to `std::vector::clear()` which destroys all $n$ elements.

### `build` (Heapify) — $O(n)$

**Algorithm:** Apply `heapifyDown` to every non-leaf node, starting from the last parent inward:

```
build([3, 1, 4, 1, 5, 9, 2, 6]):
                    3
              ┌─────┴─────┐
              1           4
          ┌───┴───┐   ┌───┴───┐
          1       5   9       2
          │
          6

  heapifyDown(3): 6 > 1 → swap        → [3, 1, 4, 6, 5, 9, 2, 1]
  heapifyDown(2): 9 > 4 → swap        → [3, 1, 9, 6, 5, 4, 2, 1]
  heapifyDown(1): 6 > 1, 5 > 1 → swap → [3, 6, 9, 1, 5, 4, 2, 1]
  heapifyDown(0): 9 > 3, 6 > 3 → swap → [9, 6, 3, 1, 5, 4, 2, 1]
                                         [9, 6, 4, 1, 5, 3, 2, 1]
```

**Proof of $O(n)$:** `build` calls `heapifyDown` on $\lfloor n/2 \rfloor$ nodes. Each call from a node at height $k$ costs $O(k)$. The total cost is:

$$T(n) = \sum_{k=0}^{\lfloor \log_2 n \rfloor} \left\lceil \frac{n}{2^{k+1}} \right\rceil \cdot O(k) = O\!\left( n \sum_{k=0}^{\infty} \frac{k}{2^k} \right) = O(n)$$

Since $\sum_{k=0}^{\infty} \frac{k}{2^k} = 2$ converges, the total is $O(n)$ — not $O(n \log n)$.

This is **faster than $n$ repeated pushes** ($O(n \log n)$).

---

## Comparison: Build Methods

| Method        | Time      | Why                          |
|---------------|-----------|------------------------------|
| $n$ pushes    | $O(n \log n)$ | Each push is $O(\log n)$  |
| `build` (heapify) | $O(n)$  | Floyd's method — most nodes are near the bottom and need few sifts |

---

## Max-Heap vs Min-Heap

| Heap type   | Comparator         | Root       | Use case                     |
|-------------|-------------------|------------|------------------------------|
| Max-heap    | `std::less<T>`    | Largest    | Priority queue (most urgent) |
| Min-heap    | `std::greater<T>` | Smallest   | Dijkstra, A*, timers         |

**Same code, different comparator.** The `heapifyUp` / `heapifyDown` logic works for both because the comparator determines the ordering:

```
comp(parent, child) is true  →  parent should be below child  →  swap
```

- `std::less`: swap when parent < child → larger rises (max-heap)
- `std::greater`: swap when parent > child → smaller rises (min-heap)

---

## Example Traces

### push sequence: 5, 3, 7, 1, 9

```
push(5): [5]
push(3): [5, 3]           heapifyUp(1): 3 < 5 → no swap
push(7): [5, 3, 7]        heapifyUp(2): 7 > 5 → swap → [7, 3, 5]
push(1): [7, 3, 5, 1]     heapifyUp(3): 1 < 3 → no swap
push(9): [7, 3, 5, 1, 9]  heapifyUp(4): 9 > 3 → swap → [7, 9, 5, 1, 3]
                            heapifyUp(1): 9 > 7 → swap → [9, 7, 5, 1, 3]
```

Final heap:
```
        9
       / \
      7   5
     / \
    1   3
```

### pop sequence from [9, 7, 5, 1, 3]

```
pop: 9  →  [3, 7, 5, 1]  heapifyDown → [7, 3, 5, 1]
pop: 7  →  [1, 3, 5]     heapifyDown → [5, 3, 1]
pop: 5  →  [1, 3]        heapifyDown → [3, 1]
pop: 3  →  [1]
pop: 1  →  []
```

---

## Applications

| Use case                       | Why heap                     |
|--------------------------------|------------------------------|
| Priority queue                 | $O(\log n)$ push/pop, $O(1)$ top |
| Heap sort                      | Build $O(n)$, pop $n$ times $O(n \log n)$ |
| $k$-way merge                  | Extract min from $k$ sorted streams |
| Dijkstra's algorithm           | Min-heap for closest vertex  |
| Median maintenance             | Max-heap for lower half, min-heap for upper half |
