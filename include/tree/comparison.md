# BST vs AVL Comparison

## Side-by-Side

| Aspect               | BST                              | AVL                              |
|----------------------|----------------------------------|----------------------------------|
| Height guarantee     | None — worst case $O(n)$         | $h \leq 1.44 \log_2 (n+1)$      |
| Node structure       | `data, left, right`              | `data, left, right, height`      |
| Memory per node      | 3 pointers / values              | +1 `int` (~4 bytes)              |
| Rotations            | None                             | Single/double rotations          |
| Balancing overhead   | $O(1)$                           | Up to $O(\log n)$ per insert/remove |

## Time Complexity

| Operation       | BST (balanced) | BST (degenerate) | AVL (guaranteed)     |
|-----------------|----------------|-------------------|----------------------|
| `insert`        | $O(\log n)$    | $O(n)$            | $O(\log n)$          |
| `contains`      | $O(\log n)$    | $O(n)$            | $O(\log n)$          |
| `remove`        | $O(\log n)$    | $O(n)$            | $O(\log n)$          |
| `min` / `max`   | $O(\log n)$    | $O(n)$            | $O(\log n)$          |
| `height`        | $O(n)$         | $O(n)$            | $O(1)$               |
| `size` / `empty`| $O(1)$         | $O(1)$            | $O(1)$               |
| `clear`         | $O(n)$         | $O(n)$            | $O(n)$               |
| `copy`          | $O(n)$         | $O(n)$            | $O(n)$               |
| traversals      | $O(n)$         | $O(n)$            | $O(n)$               |

## Empirical Behavior

### Insertion of sorted data (worst case for BST, best case for nothing)

```
BST insert 1..n:   height = n      (linked list)
AVL insert 1..n:   height ≈ 1.44 log₂ n
```

### BST — insert 1..10

```
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
           \
            7
             \
              8
               \
                9
                 \
                 10
height = 10
```

### AVL — insert 1..10

```
After rebalancing:

         4
       /   \
      2     7
     / \   / \
    1   3 6   8
         /     \
        5       9
                 \
                 10

height ≈ 4
```

## Rotation Cost

| Operation | BST    | AVL                  |
|-----------|--------|----------------------|
| `insert`  | $O(1)$ | $O(\log n)$ + at most 2 rotations |
| `remove`  | $O(1)$ | $O(\log n)$ + up to $O(\log n)$ rotations |

Each rotation is $O(1)$ (pointer reassignment + height update).

## Memory

| Aspect          | BST      | AVL         |
|-----------------|----------|-------------|
| Node fields     | 3        | 4           |
| Per-node overhead | 0      | 1 `int`    |
| For $n = 10^6$ | ~24 MB   | ~28 MB       |

AVL uses ~15% more memory for the cached height field.

## When to Use Which

### Use BST when:

1. **Insertions are random** — expected height is $O(\log n)$ anyway.
2. **Data is small** ($n < 1000$) — the $O(n)$ degenerate case is unlikely and cheap.
3. **Memory is tight** — the extra 4 bytes per node matters at scale.
4. **Simplicity matters** — fewer lines of code, easier to reason about.
5. **Data is static** — no insertions/removals after building the tree.

### Use AVL when:

1. **Guaranteed performance is required** — real-time systems, latency-sensitive code.
2. **Data arrives in sorted order** — AVL stays $O(\log n)$, BST becomes $O(n)$.
3. **Frequent lookups** — the stricter balance gives slightly shallower trees than red-black.
4. **Height queries are frequent** — $O(1)$ cached height in AVL.
5. **Worst-case must be bounded** — defence against algorithmic complexity attacks.

## AVL vs Other Self-Balancing Trees

| Tree        | Balance strictness | Insert/Remove rotations | Lookup speed |
|-------------|-------------------|------------------------|--------------|
| AVL         | Strict ($|\text{BF}| \leq 1$) | More rotations | Fastest lookups (strictest balance) |
| Red-Black   | Loose (black-height) | Fewer rotations | Slightly slower lookups |
| Splay       | None (amortized)  | Splay per operation    | Fast for repeated access |

AVL is preferred for **lookup-heavy** workloads; Red-Black for **write-heavy** workloads.

---

## Summary

| Criterion              | Winner   |
|------------------------|----------|
| Worst-case performance | **AVL**  |
| Average performance    | Tie      |
| Memory efficiency      | **BST**  |
| Implementation simplicity | **BST** |
| Guaranteed $O(\log n)$ | **AVL**  |
| Height query speed     | **AVL**  |
