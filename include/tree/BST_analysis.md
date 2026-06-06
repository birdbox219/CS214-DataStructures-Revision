# BST Analysis

## Time Complexity Summary

| Operation       | Best Case         | Average Case      | Worst Case        | Space     |
|-----------------|-------------------|-------------------|-------------------|-----------|
| `insert`        | $O(\log n)$       | $O(\log n)$       | $O(n)$            | $O(1)$    |
| `contains`      | $O(1)$            | $O(\log n)$       | $O(n)$            | $O(1)$    |
| `remove`        | $O(\log n)$       | $O(\log n)$       | $O(n)$            | $O(1)$    |
| `min` / `max`   | $O(\log n)$       | $O(\log n)$       | $O(n)$            | $O(1)$    |
| `height`        | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `size`          | $O(1)$            | $O(1)$            | $O(1)$            | $O(1)$    |
| `empty`         | $O(1)$            | $O(1)$            | $O(1)$            | $O(1)$    |
| `clear`         | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `copy`          | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `inorder`       | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `preorder`      | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `postorder`     | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |
| `bfs`           | $O(n)$            | $O(n)$            | $O(n)$            | $O(n)$    |

Where $n$ is the number of nodes and $h$ is the tree height ($1 \leq h \leq n$).

---

## BST Properties

A Binary Search Tree is a binary tree where for every node:
- All values in the **left** subtree are **less than** the node's value.
- All values in the **right** subtree are **greater than** the node's value.
- The left and right subtrees are themselves BSTs.

The tree height $h$ determines the cost of all navigational operations ($h \leq n$).

---

## Best-Case Proofs

The best case for BST operations occurs when the tree is **balanced** ($h = \Theta(\log n)$) or when the target is at the root.

### `contains` — $O(1)$

**Algorithm:** Walk left/right comparing at each node.

**Proof:** If the target value equals the root's data, the function returns `true` immediately after one comparison. No further descent is needed: $T(n) = O(1)$.

### `insert` — $O(\log n)$

**Algorithm:** Walk left/right until a null child is found, then create a new node.

**Proof:** In a perfectly balanced tree, the path from root to any insertion point is at most $\lceil \log_2 (n+1) \rceil$ nodes. Each step does $O(1)$ work, so $T(n) = O(\log n)$.

### `remove` — $O(\log n)$

**Algorithm:** Find the target, then handle leaf / one-child / two-children cases.

**Proof:** In a balanced tree, finding the node costs $O(\log n)$. In the two-child case, finding the inorder successor is another $O(\log n)$ descent. Total: $O(\log n)$.

### `min` / `max` — $O(\log n)$

**Algorithm:** Follow `left` (min) or `right` (max) until null.

**Proof:** In a balanced tree, the leftmost/rightmost path has length $O(\log n)$.

---

## Average-Case Proofs

For random insertion order, the **expected height** of a BST is $O(\log n)$. This is a classic result: the expected number of comparisons in a random BST search is approximately $2 \ln n \approx 1.39 \log_2 n$.

**Proof (expected depth):** For $n$ random insertions, the probability that the $i$-th inserted element lies on the search path of a given element $x$ is $\frac{2}{i+1}$. The expected depth of $x$ is therefore:

$$E[\text{depth}(x)] = \sum_{i=1}^{n-1} \frac{2}{i+1} = 2(H_n - 1) = O(\log n)$$

where $H_n$ is the $n$-th harmonic number ($H_n \approx \ln n + \gamma$).

Since all navigational operations (insert, contains, remove, min, max) descend along a path from root to a node, their average cost is $O(\log n)$:

| Operation | Average cost | Justification |
|-----------|-------------|---------------|
| `insert`  | $O(\log n)$ | Expected path length to leaf is $O(\log n)$ |
| `contains`| $O(\log n)$ | Expected path length to target is $O(\log n)$ |
| `remove`  | $O(\log n)$ | Find target ($O(\log n)$) + possibly find successor ($O(\log n)$) |
| `min`/`max` | $O(\log n)$ | Expected leftmost/rightmost path is $O(\log n)$ |

---

## Worst-Case Proofs

The worst case occurs when the BST becomes **degenerate** (a linked list). This happens when insertions are in sorted or reverse-sorted order: each new node appends as a right (or left) child, giving $h = n$.

### Case-Dependent (degenerate tree)

#### `insert` — $O(n)$

In a degenerate tree, walking from root to the insertion leaf visits all $n$ nodes:

$$T(n) = \sum_{i=1}^{n} 1 = n = O(n)$$

#### `contains` — $O(n)$

Every node is visited when searching for a missing value greater than all existing values (or less than all). In a degenerate tree this traverses all $n$ nodes.

#### `remove` — $O(n)$

Finding the target costs $O(n)$ in a degenerate tree. The two-child case adds another $O(n)$ successor search. Total: $O(n)$.

---

## BST Deletion Cases

Deleting a node from a BST requires maintaining the BST property. There are three cases:

### Case 1: Node is a Leaf
- Simply set the parent's pointer to null and delete the node.
- Complexity: $O(h)$ to find.

### Case 2: Node has One Child
- Replace the node with its child (bypass the node).
- Complexity: $O(h)$ to find.

### Case 3: Node has Two Children
- We cannot simply delete the node. We must replace its value with a node that is "close" in value to maintain order.
- **Option A: Inorder Successor** (Smallest node in the **right** subtree).
  1. Find the min node in the right subtree (`node->right` then follow `left` pointers).
  2. Copy the successor's value to the target node.
  3. Delete the successor (which is guaranteed to have at most one child).
- **Option B: Inorder Predecessor** (Largest node in the **left** subtree).
  1. Find the max node in the left subtree (`node->left` then follow `right` pointers).
  2. Copy the predecessor's value to the target node.
  3. Delete the predecessor.

**Successor vs Predecessor:**
- Both are equally valid.
- The successor is the node that would appear immediately after the target in an inorder traversal.
- The predecessor is the node that would appear immediately before.

---

#### `min` / `max` — $O(n)$

When the tree is a right-skewed chain, `min` traverses all $n$ nodes; when left-skewed, `max` traverses all $n$.

### Everycase (identical for best, average, worst)

These methods always process all $n$ nodes or run in constant time regardless of tree shape.

#### `height` — $O(n)$

**Algorithm:** $h(node) = \max(h(\text{left}),\, h(\text{right})) + 1$.

**Proof:** Every node is visited exactly once, even in the best case:

$$T(n) = T(k) + T(n-1-k) + O(1)$$

Unrolling gives $T(n) = O(n)$ for any $k$. Space is $O(n)$ in the worst case due to the recursion stack on a degenerate tree.

#### `clear` — $O(n)$

Post-order traversal deleting every node. Each node is visited and freed exactly once: $T(n) = O(n)$.

#### `copy` — $O(n)$

Pre-order traversal creating a new node for each source node. Each node is visited and allocated exactly once: $T(n) = O(n)$. Space: $O(n)$ for the new tree plus recursion stack.

#### `inorder`, `preorder`, `postorder` — $O(n)$

Each visits every node exactly once. Recursion depth equals $h$, so worst-case space is $O(n)$.

| Traversal   | Order                | Primary use case            |
|-------------|----------------------|-----------------------------|
| inorder     | left $\to$ node $\to$ right | Sorted output        |
| preorder    | node $\to$ left $\to$ right | Tree serialization / copy |
| postorder   | left $\to$ right $\to$ node | Tree deletion        |

#### `bfs` (Level-Order) — $O(n)$, space $O(n)$

**Algorithm:** Queue-based:
1. Push root. While queue not empty: pop front, visit, push left then right.

**Proof of $O(n)$:** Every node is enqueued once and dequeued once — all $O(1)$ operations. $T(n) = O(n)$.

**Proof of $O(n)$ space:** In a perfect binary tree, the queue holds all nodes at the widest level: $\lceil n/2 \rceil$ nodes. $S(n) = O(n)$.

**Comparison with DFS:**

| Traversal   | Order                | Data structure | Use case                     |
|-------------|----------------------|----------------|------------------------------|
| inorder     | left, node, right    | Stack (call)   | Sorted output                |
| preorder    | node, left, right    | Stack (call)   | Serialization / copy         |
| postorder   | left, right, node    | Stack (call)   | Deletion                     |
| bfs         | level by level       | Queue          | Width finding, shortest path |

#### `size` / `empty` — $O(1)$

Both use the cached `sz` counter. No traversal or computation occurs.

---

## Example Trace

Insert sequence `5, 3, 7, 1, 4, 6, 9`:

```
      5
     / \
    3   7
   / \ / \
  1  4 6  9
```

| Traversal   | Output                     |
|-------------|----------------------------|
| inorder     | 1, 3, 4, 5, 6, 7, 9       |
| preorder    | 5, 3, 1, 4, 7, 6, 9       |
| postorder   | 1, 4, 3, 6, 9, 7, 5       |
| bfs         | 5, 3, 7, 1, 4, 6, 9       |

---

## Comparison to Other Structures

| Operation | BST (balanced) | BST (degenerate) | Sorted Array | Hash Table |
|-----------|----------------|-------------------|--------------|------------|
| `insert`  | $O(\log n)$    | $O(n)$            | $O(n)$       | $O(1)$     |
| `contains`| $O(\log n)$    | $O(n)$            | $O(\log n)$  | $O(1)$     |
| `remove`  | $O(\log n)$    | $O(n)$            | $O(n)$       | $O(1)$     |
| `min`/`max`| $O(\log n)$   | $O(n)$            | $O(1)$       | $O(n)$     |
| sorted order | $O(n)$     | $O(n)$            | $O(1)$       | $O(n \log n)$ |

Self-balancing trees (AVL, Red-Black) guarantee $h = O(\log n)$, eliminating the degenerate worst case.
