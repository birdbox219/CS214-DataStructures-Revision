# Graph Analysis

## Graph Fundamentals

A **Graph** $G = (V, E)$ consists of a set of vertices (nodes) $V$ and a set of edges $E$ connecting them.

### Key Distinctions
- **Directed vs. Undirected:** Directed edges have a source and destination ($u \to v$); undirected edges are bidirectional ($u - v$).
- **Weighted vs. Unweighted:** Weighted edges have an associated cost (distance, weight).
- **Cyclic vs. Acyclic:** A cycle is a path where the first and last vertices are the same.
- **Tree vs. Graph:** A **Tree** is a special type of graph that is **connected** and **acyclic**. A graph with $n$ vertices is a tree if and only if it is connected and has $n-1$ edges.

---

## Graph Representations

### 1. Adjacency Matrix
A 2D array `adj[V][V]` where `adj[i][j] = 1` if an edge exists from $i$ to $j$, and `0` otherwise.

| Operation | Complexity |
|-----------|------------|
| Space | $O(V^2)$ |
| Add Edge | $O(1)$ |
| Remove Edge | $O(1)$ |
| Check Edge | $O(1)$ |
| Find Neighbors | $O(V)$ |

**Pros:** Constant time edge checks, simple implementation.
**Cons:** High space complexity; inefficient for sparse graphs.

### 2. Adjacency List
An array of lists (or vectors) where `adj[i]` contains all vertices adjacent to vertex $i$.

| Operation | Complexity |
|-----------|------------|
| Space | $O(V + E)$ |
| Add Edge | $O(1)$ |
| Remove Edge | $O(E/V)$ average |
| Check Edge | $O(E/V)$ average |
| Find Neighbors | $O(\text{degree}(V))$ |

**Pros:** Space efficient for sparse graphs; fast iteration over neighbors.
**Cons:** Slower to check if a specific edge exists.

---

## Graph Traversals

### 1. Breadth-First Search (BFS)
Explores neighbors level by level.

**Algorithm:**
1. Use a **Queue** and a `visited` array.
2. Mark source as visited and enqueue it.
3. While queue is not empty:
   - Dequeue $u$, process it.
   - For each neighbor $v$ of $u$:
     - If $v$ is not visited, mark visited and enqueue.

**Complexity:** $O(V + E)$ with Adjacency List.
**Primary Use:** Finding shortest path in unweighted graphs.

### 2. Depth-First Search (DFS)
Explores as far as possible along each branch before backtracking.

**Algorithm:**
1. Use a **Stack** (or recursion) and a `visited` array.
2. Mark source as visited and push to stack.
3. While stack is not empty:
   - Pop $u$, process it.
   - For each neighbor $v$ of $u$:
     - If $v$ is not visited, mark visited and push to stack.

**Complexity:** $O(V + E)$ with Adjacency List.
**Primary Use:** Topological sort, cycle detection, path finding.

---

## Comparison Summary

| Traversal | Data Structure | Strategy |
|-----------|----------------|----------|
| BFS | Queue | Level-order |
| DFS | Stack / Recursion | Path-depth |
