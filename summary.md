# Data Structures Summary

## Linear Structures

### ArrayList
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `pushBack` | $O(1)$ | $O(1)$\* | $O(n)$\* | $O(1)$ |
| `popBack` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `pushFront` / `popFront` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `insert` / `remove` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `get` / `operator[]` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `contains` | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ |

\*Amortized.

### LinkedList (Singly)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `pushFront` / `pushBack` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `popFront` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `popBack` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `insert` / `remove` / `get` | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `reverse` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |

### DLL (Doubly Linked List)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `pushFront` / `pushBack` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `popFront` / `popBack` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `insert` / `remove` / `get` | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `reverse` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |

### Stack (LIFO)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `push` | $O(1)$ | $O(1)$\* | $O(n)$\* | $O(1)$ |
| `pop` / `top` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |

\*Amortized.

### Queue (FIFO)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `push` / `pop` / `front` / `back` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |

### CircularQueue (Ring Buffer)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `push` | $O(1)$ | $O(1)$\* | $O(n)$\* | $O(1)$ |
| `pop` / `front` / `back` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |

\*Amortized.

### PriorityQueue (Heap-Based)
| Operation | Complexity | Space |
|---|---|---|
| `push` / `pop` | $O(\log n)$ | $O(1)$ |
| `top` | $O(1)$ | $O(1)$ |

### OrderedList (Sorted Array)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `insert` | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| `find` / `contains` | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ |
| `get` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |

## Tree Structures

### BST (Binary Search Tree)
| Operation | Best | Average | Worst | Space |
|---|---|---|---|---|
| `insert` / `contains` / `remove` | $O(\log n)$ | $O(\log n)$ | $O(n)$ | $O(1)$ |
| `min` / `max` | $O(\log n)$ | $O(\log n)$ | $O(n)$ | $O(1)$ |
| traversals / `height` | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |

### AVL Tree (Self-Balancing BST)
| Operation | Complexity | Space |
|---|---|---|
| `insert` / `contains` / `remove` | $O(\log n)$ | $O(\log n)$ |
| `height` | $O(1)$ | $O(1)$ |
| traversals | $O(n)$ | $O(n)$ |

Height bound: $h \leq 1.44 \log_2 (n+1)$

### Heap (Binary Heap)
| Operation | Complexity | Space |
|---|---|---|
| `push` / `pop` | $O(\log n)$ | $O(1)$ |
| `top` | $O(1)$ | $O(1)$ |
| `build` (Floyd) | $O(n)$ | $O(n)$ |

## Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|---|---|---|---|---|---|
| Bubble Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| Selection Sort | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | No |
| Insertion Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| Merge Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(n)$ | Yes |
| Quick Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n^2)$ | $O(\log n)$ | No |
| Heap Sort | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(1)$ | No |
| Counting Sort | $O(n+k)$ | $O(n+k)$ | $O(n+k)$ | $O(k)$ | Yes |
| Radix Sort | $O(d(n+b))$ | $O(d(n+b))$ | $O(d(n+b))$ | $O(n+b)$ | Yes |

## Memory Overhead (Per Element)

| Structure | Overhead |
|---|---|
| ArrayList | 0 (contiguous, cap slack possible) |
| LinkedList | 1 pointer (~8 bytes) |
| DLL | 2 pointers (~16 bytes) |
| Stack / Queue | same as backing structure |
| BST / AVL | 2 child ptrs; AVL adds +1 `int` |
| Heap | 0 (`std::vector`) |

## File Layout

```
include/
├── linear/
│   ├── ArrayList.h .tpp _analysis.md
│   ├── LinkedList.h .tpp _analysis.md
│   ├── DLL.h .tpp _analysis.md          (+ XOR trick)
│   ├── Stack.h .tpp _analysis.md
│   ├── Queue.h .tpp _analysis.md
│   ├── CircularQueue.h .tpp _analysis.md
│   ├── PriorityQueue.h .tpp _analysis.md
│   └── OrderedList.h .tpp _analysis.md
├── tree/
│   ├── BST.h .tpp _analysis.md
│   ├── AVL.h .tpp _analysis.md + comparison.md
│   └── Heap.h .tpp _analysis.md
├── graph/
│   └── analysis.md
├── sorting/
│   ├── Sort.h .tpp
│   └── analysis.md
src/                    (mirrors include/ with .tpp)
```

## Revision Resources

- **Written_Questions.md** — Common exam questions and conceptual challenges.
- **Answers.md** — Detailed answers and tracing for the written questions.

## Key Distinctions

| Scenario | Best Choice |
|---|---|
| Front-heavy insert/remove | LinkedList / DLL |
| Random access | ArrayList |
| Bidi operations + O(1) popBack | DLL |
| Guaranteed O(log n) search | AVL |
| Dynamic priority | Heap / PriorityQueue |
| Sorted lookup + random access | OrderedList |
| Fixed-capacity FIFO | CircularQueue |
| LIFO | Stack |
