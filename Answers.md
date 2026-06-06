# Data Structures: Answers to Conceptual Questions

## Linear Structures

### A1: ArrayList vs. LinkedList
- **Memory Allocation:** `ArrayList` uses a single contiguous block (better cache locality). `LinkedList` uses fragmented nodes connected by pointers.
- **Random Access:** `ArrayList` is $O(1)$ via index. `LinkedList` is $O(n)$ as it requires traversal.
- **Front Operations:** `ArrayList` is $O(n)$ due to shifting. `LinkedList` is $O(1)$ by updating the head pointer.

### A2: Stack Applications
A **Stack** (LIFO) is the best choice. Opening brackets are pushed onto the stack, and when a closing bracket is encountered, it must match the most recently pushed opening bracket (the one at the top).

### A3: Circular Queue Logic
- **Logic:** Uses the modulo operator `%` to wrap the `tail` or `head` index back to `0` when it reaches the end of the array (`(tail + 1) % capacity`).
- **Preference:** A standard array queue requires shifting elements $O(n)$ after every dequeue to free space. A Circular Queue allows $O(1)$ enqueue and dequeue by reusing vacated slots at the beginning of the array.

### A4: Postfix Evaluation
Expression: `8 5 3 * + 8 2 / -`
1. Read `8`: Stack `[8]`
2. Read `5`: Stack `[8, 5]`
3. Read `3`: Stack `[8, 5, 3]`
4. Read `*`: `5 * 3 = 15`. Stack `[8, 15]`
5. Read `+`: `8 + 15 = 23`. Stack `[23]`
6. Read `8`: Stack `[23, 8]`
7. Read `2`: Stack `[23, 8, 2]`
8. Read `/`: `8 / 2 = 4`. Stack `[23, 4]`
9. Read `-`: `23 - 4 = 19`. Stack `[19]`
**Result: 19.**

## Tree Structures

### A5: Heap Representation
- **Why Array:** Since a binary heap is a **Complete Binary Tree**, there are no gaps between nodes. This allows a compact array representation without pointer overhead ($O(1)$ space per element).
- **Indices:** For a node at index $i$:
  - Left Child: `2i + 1`
  - Right Child: `2i + 2`
  - Parent: `(i - 1) / 2`

### A6: AVL Tree Balancing
- **Bound:** $h \leq 1.44 \log_2(n+1)$.
- **Importance:** It guarantees that the tree height remains logarithmic, ensuring that `insert`, `delete`, and `search` operations are strictly $O(\log n)$ even in the worst case.

### A7: BST Deletion
1. **Inorder Successor:** The smallest node in the right subtree. Found by going `right` once, then `left` as far as possible.
2. **Inorder Predecessor:** The largest node in the left subtree. Found by going `left` once, then `right` as far as possible.

### A8: BST vs. Hash Table
- **BST Search:** $O(\log n)$. **Hash Table Search:** $O(1)$ average.
- **BST Preference:** When you need **ordered data** (e.g., printing all elements in sorted order) or performing **range queries** (e.g., finding all elements between $X$ and $Y$). Hash tables do not maintain order.

## Sorting & Complexity

### A9: Sorting Lower Bound
- **Theorem:** Any comparison-based sorting algorithm requires $\Omega(n \log n)$ comparisons in the worst case.
- **Logic:** A sorting algorithm is a decision tree with $n!$ leaves (possible permutations). A binary tree with $L$ leaves has height $h \geq \log_2 L$. Thus, $h \geq \log_2(n!) \approx n \log n$.

### A10: Quickselect Average Case
- **Complexity:** Average $O(n)$, Worst $O(n^2)$.
- **Difference:** Quick Sort recurses on **both** sides of the pivot ($T(n) = 2T(n/2) + n = O(n \log n)$). Quickselect recurses on only **one** side ($T(n) = T(n/2) + n = O(n)$).

### A11: Stability in Sorting
- **Definition:** A sorting algorithm is stable if it preserves the relative order of equal elements.
- **Stable:** Merge Sort / Insertion Sort.
- **Unstable:** Quick Sort / Heap Sort / Selection Sort.

## Graphs

### A12: Graph vs. Tree
A **Tree** is a graph that is:
1. **Connected** (path exists between any two vertices).
2. **Acyclic** (contains no cycles).
3. Alternatively: A connected graph with exactly $V-1$ edges.

### A13: Traversal Data Structures
- **BFS:** Queue (FIFO).
- **DFS:** Stack (LIFO) or Recursion (using the system call stack).

## Recursion

### A14: Recursion Depth
- **Risk:** **Stack Overflow** due to excessive memory usage on the call stack if recursion depth is too high (e.g., $O(n)$ depth on a large input).
- **Mitigation:** Convert recursion to an iterative algorithm using an explicit stack, or use **tail-call optimization** (if supported), or use balanced data structures (like AVL trees) to ensure $O(\log n)$ depth.
