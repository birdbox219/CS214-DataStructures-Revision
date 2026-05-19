# CS214 — Data Structures (Revision)

This repository contains a comprehensive **revision reference** for the **Data Structures** course (CS214). It provides clean, template-based C++17 implementations of the core data structures taught in the curriculum, along with detailed analysis documents covering time/space complexity proofs, best/average/worst-case behaviors, and comparison tables.

## Contents

### Linear Structures
- **ArrayList** — Dynamic array with amortized O(1) pushBack, O(1) random access
- **LinkedList** — Singly linked list with head/tail pointers
- **DLL** — Doubly linked list with O(1) popBack, XOR trick reference
- **Stack** — LIFO on dynamic array
- **Queue** — FIFO on singly linked nodes
- **CircularQueue** — Ring buffer with wrap-around indices and auto-resize
- **PriorityQueue** — Adapter wrapping a binary heap
- **OrderedList** — Sorted dynamic array with binary search

### Tree Structures
- **BST** — Binary Search Tree (no balancing, degenerate worst case O(n))
- **AVL** — Self-balancing BST (guaranteed O(log n) height)
- **Heap** — Binary heap with comparator-tunable max/min semantics

### Sorting Algorithms
- Bubble, Selection, Insertion, Merge, Quick, Heap, Counting, Radix Sort
- Includes Ω(n log n) lower bound proof

## File Layout

```
include/linear/     — headers + analysis docs for linear structures
include/tree/       — headers + analysis docs for tree structures
include/sorting/    — header + analysis doc for sorting algorithms
src/linear/         — template implementations (.tpp)
src/tree/
src/sorting/
```

## Analysis Documents

Each data structure includes a corresponding `*_analysis.md` with:
- Time complexity summary table (best / average / worst / space)
- Per-operation proofs with recurrence relations
- Memory overhead comparison
- Example traces
- Comparison with alternative implementations
