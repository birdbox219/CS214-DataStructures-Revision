# AVL Tree Analysis

## Time Complexity Summary

| Operation       | Best / Average / Worst | Space     |
|-----------------|------------------------|-----------|
| `insert`        | $O(\log n)$            | $O(\log n)$ |
| `contains`      | $O(\log n)$            | $O(1)$    |
| `remove`        | $O(\log n)$            | $O(\log n)$ |
| `min` / `max`   | $O(\log n)$            | $O(1)$    |
| `height`        | $O(1)$                 | $O(1)$    |
| `size`          | $O(1)$                 | $O(1)$    |
| `empty`         | $O(1)$                 | $O(1)$    |
| `clear`         | $O(n)$                 | $O(n)$    |
| `copy`          | $O(n)$                 | $O(n)$    |
| `inorder`       | $O(n)$                 | $O(n)$    |
| `preorder`      | $O(n)$                 | $O(n)$    |
| `postorder`     | $O(n)$                 | $O(n)$    |
| `bfs`           | $O(n)$                 | $O(n)$    |

All navigational operations are **guaranteed** $O(\log n)$ — there is no degenerate worst case.

$n$ = number of nodes. The height $h$ **always** satisfies $h \leq 1.44 \log_2(n+1)$.

---

## Properties

An AVL tree is a self-balancing BST where for every node:

$$|\text{height(left)} - \text{height(right)}| \leq 1$$

This **balance invariant** is maintained after every insertion and deletion via rotations.

**Height bound:** The minimum number of nodes in an AVL tree of height $h$ is $F_{h+3} - 1$ (shifted Fibonacci), giving:

$$h \leq \log_\varphi (n + 1) \approx 1.44 \log_2 (n + 1)$$

where $\varphi = \frac{1 + \sqrt{5}}{2} \approx 1.618$.

**Proof (worst-case height):** Let $N(h)$ be the minimum number of nodes in an AVL tree of height $h$. The worst case occurs when the balance factor is $\pm 1$ at every node:

$$N(0) = 0,\quad N(1) = 1,\quad N(h) = 1 + N(h-1) + N(h-2)$$

This is $N(h) = F_{h+3} - 1$ where $F_k$ is the $k$-th Fibonacci number ($F_{h+3} \approx \varphi^{h+3} / \sqrt{5}$). Solving for $h$:

$$n = N(h) \;\Longrightarrow\; h \leq \log_\varphi (n + 1) = O(\log n)$$

---

## Rotations

Four rotation cases maintain the balance invariant after insertions and deletions.

### Right Rotation (LL)

```
    y              x
   / \            / \
  x   T3   →     T1  y
 / \                / \
T1 T2              T2 T3
```

Trigger: balance > 1 and left child's balance >= 0.

### Left Rotation (RR)

```
  x                y
 / \              / \
T1  y      →     x   T3
   / \          / \
  T2 T3        T1 T2
```

Trigger: balance < -1 and right child's balance <= 0.

### Left-Right Rotation (LR)

```
    y                y               z
   / \              / \            /   \
  x   T4    →      z   T4   →    x      y
 / \              / \           / \    / \
T1  z            x   T3        T1 T2  T3 T4
   / \          / \
  T2 T3        T1 T2
```

Trigger: balance > 1 and left child's balance < 0.

### Right-Left Rotation (RL)

```
  x                x                 z
 / \              / \              /   \
T1  y      →     T1  z      →    x      y
   / \              / \         / \    / \
  z   T4           T2  y       T1 T2  T3 T4
 / \                  / \
T2 T3                T3 T4
```

Trigger: balance < -1 and right child's balance > 0.

---

## Per-Operation Proofs

### `insert` — $O(\log n)$

1. Perform standard BST descent to find the insertion point: $O(\log n)$.
2. Create a new node (height = 1).
3. Walk back up the recursion path, updating heights and checking balance factors.
4. If imbalance is detected ($|\text{balance}| > 1$), perform one or two rotations.
5. Each rotation is $O(1)$. At most one rotation (single or double) occurs per insertion.
6. Total: $O(\log n)$ search + $O(1)$ rotation = $O(\log n)$.

### `remove` — $O(\log n)$

1. Find the target node: $O(\log n)$.
2. Delete it (leaf / one child / two children with successor).
3. Walk back up the recursion path, updating heights and rebalancing.
4. Unlike insert, up to $O(\log n)$ rotations may be needed on the path back to the root.
5. Each rotation is $O(1)$, so total: $O(\log n)$.

### `contains` — $O(\log n)$

Standard BST search, guaranteed $O(\log n)$ because $h = O(\log n)$.

### `min` / `max` — $O(\log n)$

Follow left (min) or right (max) pointers. Path length $\leq h = O(\log n)$.

### `height` — $O(1)$

Returns `root ? root->height : 0`. Height is cached in each node and maintained during insert/remove. No traversal needed.

### `size` / `empty` — $O(1)$

Uses the cached `sz` counter.

### `clear` — $O(n)$

Post-order traversal deleting every node. Each node is visited and freed exactly once.

### `copy` — $O(n)$

Pre-order traversal creating one new node per source node. Heights are set correctly from the recursive results.

### Traversals — $O(n)$

| Traversal   | Order                | Use case                     |
|-------------|----------------------|------------------------------|
| inorder     | left, node, right    | Sorted output                |
| preorder    | node, left, right    | Serialization / copy         |
| postorder   | left, right, node    | Deletion                     |
| bfs         | level by level       | Width finding, level-order   |

Each visits $n$ nodes exactly once.

---

## Insertion Example

Insert `5, 3, 7, 1, 4, 6, 9` into an AVL tree:

```
Step 1: insert(5)    Step 2: insert(3)    Step 3: insert(7)
  5 (h=1)            5 (h=2)              5 (h=2)
                     /                    / \
                    3 (h=1)             3   7 (both h=1)

Step 4: insert(1)    balance(3)=0, balance(5)=1  →  OK
  5 (h=3)
 / \
3   7
/
1 (h=1)

Step 5: insert(4)
      5 (h=3)
     / \
    3   7
   / \
  1   4
      ↑ balance(3)=-1, balance(5)=1  → LR at 5

After LR rotation:
      4 (h=2)
     / \
    3   5
   /     \
  1       7
         /
        6

Step 6: insert(6)    balance(7)=1   → OK
After rebalance:
      4 (h=3)
     / \
    3   6
   /   / \
  1   5   7

Step 7: insert(9)    balance(6)=-2  → RR at 6
After RR rotation:
      4 (h=3)
     / \
    3   6
   /   / \
  1   5   7
           \
            9

Final tree height: 3  (vs height 4 in unbalanced BST)
```
