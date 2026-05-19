# CircularQueue Analysis

## Time Complexity Summary

| Operation     | Best Case | Average Case | Worst Case | Space     |
|---------------|-----------|--------------|------------|-----------|
| `push`        | $O(1)$    | $O(1)$*      | $O(n)$*    | $O(1)$    |
| `pop`         | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `front`       | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `back`        | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |
| `size` / `capacity` / `empty` / `full` | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| `clear`       | $O(1)$    | $O(1)$       | $O(1)$     | $O(1)$    |

$n$ = number of elements. \*Amortized $O(1)$ for `push`; $O(n)$ when a resize occurs.

---

## Properties

A **CircularQueue** (ring buffer) is a FIFO (First-In-First-Out) queue backed by a fixed-size dynamic array that reuses memory by wrapping indices around.

- Elements stored contiguously in `arr`, but logical order wraps from `head` to just before `tail`
- `head` — index of the next element to pop (front of queue)
- `tail` — index of the next insertion position (back of queue)
- `sz` — number of elements currently stored
- Logical state: **empty** when `sz == 0`; **full** when `sz == cap`
- On push when full, resizes to $2 \times cap$, re-linearizing elements so `head = 0`, `tail = sz`
- All operations are $O(1)$ except push when resize occurs
- No element shifting — only pointer/index arithmetic

---

## Per-Operation Proofs

### `push` — $O(1)$ amortized

**Algorithm:** If `sz == cap`, resize to `2 * cap`. Place `val` at `arr[tail]`, then `tail = (tail + 1) % cap`, increment `sz`.

**Proof:** When no resize: one store, one increment, one modulo — $T(n) = O(1)$. When resizing, all $n$ elements are copied: $O(n)$. By the banker's accounting argument, charging 3 tokens per push pays for the future copy of each element, giving $O(1)$ amortized.

### `pop` — $O(1)$

**Algorithm:** If empty, throw. Advance `head = (head + 1) % cap`, decrement `sz`.

**Proof:** No data movement. $T(n) = O(1)$.

### `front` / `back` — $O(1)$

**Algorithm:** `front` returns `arr[head]`; `back` returns `arr[(tail - 1 + cap) % cap]`. Both bounds-check first.

**Proof:** Direct index access. $T(n) = O(1)$.

### `size` / `capacity` / `empty` / `full` — $O(1)$

Return cached fields or simple comparisons.

### `clear` — $O(1)$

Set `head = tail = sz = 0`.

---

## Memory

| Aspect               | Array-based (implemented)      | Linked-list-based (conceptual) |
|----------------------|--------------------------------|--------------------------------|
| Per-element overhead | 0 (elements only)              | 1 pointer (~8 bytes)           |
| Allocation           | Single contiguous block        | Per node (fragmented)          |
| Slack                | $(cap - sz) \times T$ wasted   | 0 exact allocation             |
| Cache locality       | Excellent (sequential)         | Poor (pointer chasing)         |
| Resize cost          | $O(n)$ copy                    | No resize (per-node alloc)     |

The array-based approach wastes at most $cap - sz$ slots but benefits from cache-friendly sequential access. The linked-list approach allocates exactly per element but incurs per-node overhead and poor locality.

---

## Comparison: Array-based vs Linked-list-based Queue

| Operation  | Array-based (CircularQueue) | Linked-list-based Queue |
|------------|------------------------------|-------------------------|
| `push`     | $O(1)$ amortized             | $O(1)$                  |
| `pop`      | $O(1)$                       | $O(1)$                  |
| `front`    | $O(1)$                       | $O(1)$                  |
| `back`     | $O(1)$                       | $O(n)$ (no tail ptr) or $O(1)$ (with tail ptr) |
| Memory     | Contiguous, low overhead     | Fragmented, per-node ptr overhead |
| Cache      | Excellent                    | Poor                    |
| Resize     | $O(n)$ copy (rare)           | No resize needed        |

**When to use array-based:** High-performance scenarios, cache-sensitive code, predictable capacity, or when `back` access is frequent.

**When to use linked-list-based:** Unpredictable growth (avoiding resizes), real-time systems (avoiding $O(n)$ copy latency), or when per-element overhead is acceptable.

---

## Applications

Circular queues (ring buffers) are widely used in systems programming and real-time applications:

- **I/O ring buffers** — Keyboard/mouse event buffers, network packet queues. The fixed-size circular buffer prevents unbounded memory growth and provides $O(1)$ enqueue/dequeue.
- **Audio / video streaming** — Frame buffers where producers (encoder) and consumers (decoder) run at different rates. The circular buffer decouples them.
- **Serial communication** (UART, SPI) — Hardware ring buffers for asynchronous byte reception/transmission.
- **Task scheduling** — Fixed-size task queues in embedded RTOS kernels.
- **Logging** — Circular log buffers that keep the most recent $N$ entries, overwriting the oldest when full (useful for crash dump ring buffers).
- **Graphics** — Command buffer rings in GPU driver pipelines (e.g., Vulkan swap chains).
- **Online statistics** — Sliding window statistics (moving average, min/max over last $N$ samples).

The key advantage in all these cases is that no dynamic allocation occurs during normal operation once the buffer reaches capacity (the `full()` state), making it suitable for hard real-time constraints.

---

## Example Trace

### Push sequence: `push(1), push(2), push(3), push(4), push(5)` (initial cap = 4)

```
Initial: cap=4, head=0, tail=0, sz=0, arr=[_, _, _, _]

Step 1: push(1)
    arr[0] = 1, tail=1, sz=1     arr=[1, _, _, _]    head=0, tail=1

Step 2: push(2)
    arr[1] = 2, tail=2, sz=2     arr=[1, 2, _, _]    head=0, tail=2

Step 3: push(3)
    arr[2] = 3, tail=3, sz=3     arr=[1, 2, 3, _]    head=0, tail=3

Step 4: push(4)
    arr[3] = 4, tail=0, sz=4     arr=[1, 2, 3, 4]    head=0, tail=0 (full)

Step 5: push(5)
    full → resize(8)
    copy in order: [1,2,3,4] → [1,2,3,4,_,_,_,_]
    head=0, tail=4
    arr[4] = 5, tail=5, sz=5     arr=[1,2,3,4,5,_,_,_]  head=0, tail=5
```

### Pop sequence: `pop(), pop(), push(6), push(7), pop()`

```
Start:  arr=[1,2,3,4,5,_,_,_]    head=0, tail=5, sz=5

pop():  head=1, sz=4             front is now arr[1]=2
pop():  head=2, sz=3             front is now arr[2]=3
push(6):
    arr[5] = 6, tail=6, sz=4     arr=[1,2,3,4,5,6,_,_]
push(7):
    arr[6] = 7, tail=7, sz=5     arr=[1,2,3,4,5,6,7,_]
pop():  head=3, sz=4             front is now arr[3]=4

Final:  arr=[1,2,3,4,5,6,7,_]    head=3, tail=7, sz=4
    logical order: arr[3]=4, arr[4]=5, arr[5]=6, arr[6]=7
```

### Wrap-around behavior

```
Push after tail wraps:
    push(8):
        arr[7] = 8, tail=0, sz=5     arr=[1,2,3,4,5,6,7,8]
    push(9):
        arr[0] = 9, tail=1, sz=6     arr=[9,2,3,4,5,6,7,8] (wrapped!)

    Logical order: arr[3]=4, arr[4]=5, arr[5]=6, arr[6]=7, arr[7]=8, arr[0]=9
    front = arr[head] = arr[3] = 4
    back  = arr[(tail-1+cap)%cap] = arr[0] = 9
```
