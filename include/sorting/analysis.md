# Sorting Algorithm Analysis

## Time Complexity Summary

| Algorithm          | Best Case     | Average Case  | Worst Case    | Space     | Stable |
|--------------------|---------------|---------------|---------------|-----------|--------|
| Bubble Sort        | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$    | Yes    |
| Selection Sort     | $O(n^2)$      | $O(n^2)$      | $O(n^2)$      | $O(1)$    | No     |
| Insertion Sort     | $O(n)$        | $O(n^2)$      | $O(n^2)$      | $O(1)$    | Yes    |
| Merge Sort         | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$    | Yes    |
| Quick Sort         | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$      | $O(\log n)$ | No   |
| Heap Sort          | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$    | No     |
| Counting Sort      | $O(n + k)$    | $O(n + k)$    | $O(n + k)$    | $O(k)$    | Yes    |
| Radix Sort         | $O(d(n+b))$   | $O(d(n+b))$   | $O(d(n+b))$   | $O(n+b)$  | Yes    |

Where $n$ is the number of elements, $k$ is the value range, $d$ is the digit count, and $b$ is the base.

---

## Best-Case Proofs

### Insertion Sort — $O(n)$

When the array is already sorted, each key is already in its correct position.

$$T(n) = \sum_{i=2}^{n} 1 = n - 1 = O(n)$$

The inner loop body never executes; only one comparison per element occurs.

### Quick Sort — $O(n \log n)$

The best case occurs when every pivot splits the array into two equal halves. The recurrence is:

$$T(n) = 2T\!\left(\frac{n}{2}\right) + O(n)$$

Unrolling:
$$T(n) = 2T\!\left(\frac{n}{2}\right) + cn$$

$$= 2\left[2T\!\left(\frac{n}{4}\right) + \frac{cn}{2}\right] + cn
 = 4T\!\left(\frac{n}{4}\right) + 2cn$$

$$= 2^k T\!\left(\frac{n}{2^k}\right) + k \cdot cn$$

The base case $T(1) = O(1)$ is reached when $\frac{n}{2^k} = 1$, so $k = \log_2 n$:

$$T(n) = n \cdot T(1) + cn \log_2 n = O(n) + O(n \log n) = O(n \log n)$$

### Merge Sort — $O(n \log n)$

Merge Sort always divides into equal halves and merges in $O(n)$, giving the same recurrence as the best case of Quick Sort, so $T(n) = O(n \log n)$ in every case.

---

## Average-Case Proofs

### Quick Sort — $O(n \log n)$ (Corrected)

Let $T(n)$ be the **expected** number of comparisons. For a random pivot, the larger of the two resulting subarrays has expected size $\frac{3}{4}n$:

$$
E[\max(k,\, n-1-k)] = \frac{1}{n} \sum_{k=\lceil n/2 \rceil}^{n-1} 2k \approx \frac{3}{4}n
$$

Each partition step does $O(n)$ work, and every element recurses at most $O(\log_{4/3} n)$ times (since each recursive call shrinks the subarray by a factor of $\frac{3}{4}$ on average). The expected total work is therefore bounded by:

$$
T(n) = O(n) \cdot O(\log_{4/3} n) = O(n \log n)
$$

A tighter derivation via the expected-value recurrence $T(n) = (n-1) + \frac{2}{n}\sum_{k=0}^{n-1} T(k)$ yields the exact constant $T(n) = 2(n+1)H_n - 4n \approx 2n \ln n$, confirming $O(n \log n)$.

### Insertion Sort — $O(n^2)$

On average, each key must travel halfway through the already-sorted portion:

$$T(n) = \sum_{i=2}^{n} \frac{i}{2} = \frac{1}{2} \cdot \frac{n(n-1)}{2} = \frac{n(n-1)}{4} = O(n^2)$$

### Bubble Sort — $O(n^2)$

On average, approximately half the elements are out of order, so the inner loop does not terminate early. The expected number of passes is $O(n)$, yielding $T(n) = O(n^2)$.

---

## Worst-Case Proofs

### Selection Sort — $O(n^2)$

The inner loop always scans the full unsorted portion regardless of data order:

$$T(n) = \sum_{i=1}^{n-1} (n-i) = \frac{n(n-1)}{2} = O(n^2)$$

No early termination exists; best, average, and worst cases are identical.

### Insertion Sort — $O(n^2)$

When the array is reverse-sorted, each key travels all the way to the front:

$$T(n) = \sum_{i=2}^{n} (i-1) = \frac{n(n-1)}{2} = O(n^2)$$

### Bubble Sort — $O(n^2)$

Without early termination (or when the smallest element is at the end), all $n-1$ passes execute:

$$T(n) = \sum_{i=1}^{n-1} (n-i) = \frac{n(n-1)}{2} = O(n^2)$$

### Quick Sort — $O(n^2)$

When the pivot is always the minimum or maximum element (e.g., already sorted or reverse-sorted array with Lomuto partition), one partition is empty and the other has $n-1$ elements:

$$T(n) = T(0) + T(n-1) + O(n) = T(n-1) + O(n)$$

Unrolling:

$$T(n) = \sum_{i=1}^{n} O(i) = O(n^2)$$

### Merge Sort — $O(n \log n)$

Same recurrence as the best case (always divides equally):

$$T(n) = 2T\!\left(\frac{n}{2}\right) + O(n)$$

Unrolling (see Best-Case Quick Sort) gives $T(n) = \Theta(n \log n)$.

### Heap Sort — $O(n \log n)$

Heap Sort is everycase: all inputs run in $\Theta(n \log n)$.

**Algorithm:**
1. **Build** a max-heap from the array using Floyd's method: $O(n)$.
2. **Extract** the root $n$ times: swap it with the last unsorted element, reduce the heap size, and sift the new root down.

**Proof of $O(n \log n)$:**

The build phase runs `shiftDown` on $\lfloor n/2 \rfloor$ nodes. Each sift from height $k$ costs $O(k)$. The total build cost is:

$$T_{\text{build}}(n) = \sum_{k=0}^{\lfloor \log_2 n \rfloor} \left\lceil \frac{n}{2^{k+1}} \right\rceil \cdot O(k) = O(n)$$

(The infinite series $\sum k/2^k$ converges to $2$.)

The extraction phase runs $n-1$ iterations. Each iteration swaps the root and calls `siftDown` on a heap of size $i$, which costs $O(\log i)$:

$$T_{\text{extract}}(n) = \sum_{i=2}^{n} O(\log i) = O(\log n!) = O(n \log n)$$

Using Stirling's approximation $\log(n!) = n \log n - n \log e + O(\log n) = \Theta(n \log n)$.

Total: $T(n) = O(n) + O(n \log n) = O(n \log n)$.

**Space:** $O(1)$ — sorts in place with no extra storage (unlike Merge Sort). Not stable.

### Counting Sort — $O(n + k)$

Each step is linear in $n$ or $k$:

$$
\begin{aligned}
\text{Find min/max} &: O(n) \\
\text{Count frequencies} &: O(n) \\
\text{Prefix sum} &: O(k) \\
\text{Build output} &: O(n) \\
\hline
\text{Total} &: O(n + k)
\end{aligned}
$$

When $k = O(n)$, this simplifies to $O(n)$.

### Radix Sort — $O(d(n + b))$

Let $d$ be the number of digits and $b$ the base. Each digit pass performs a stable counting sort ($O(n + b)$) for $d$ passes:

$$T(n) = d \cdot O(n + b) = O(d(n + b))$$

Since $d \leq \log_b(\max)$, equivalently $T(n) = O\!\left((n + b) \log_b(\max)\right)$. With $b = O(n)$ and $d = O(1)$, this simplifies to $O(n)$.

---

## Lower Bound: Comparison-Based Sorting Is $\Omega(n \log n)$

**Theorem.** Any comparison-based sorting algorithm requires $\Omega(n \log n)$ comparisons in the worst case.

**Proof (Decision Tree Model).**

A comparison-based sorting algorithm can be modeled as a **binary decision tree**:
- Each internal node represents a comparison $a_i : a_j$ (two outcomes: $\leq$ or $>$).
- Each leaf represents a distinct permutation that is the correct sorted order.
- The path from root to leaf is the exact sequence of comparisons made for a given input.

For $n$ distinct elements, there are $n!$ possible permutations. Since the algorithm must distinguish every permutation, the decision tree must have **at least $n!$ leaves**.

A binary tree of height $h$ (the maximum number of comparisons in any execution) has **at most $2^h$ leaves**. Therefore:

$$2^h \ge n! \quad\Longrightarrow\quad h \ge \log_2(n!)$$

Stirling's approximation gives $\log_2(n!) = n \log_2 n - n \log_2 e + O(\log n)$:

$$n! \sim \sqrt{2\pi n}\left(\frac{n}{e}\right)^n
\;\Longrightarrow\;
\log_2(n!) = n \log_2 n - \frac{n}{\ln 2} + O(\log n) = \Theta(n \log n)$$

Thus $h = \Omega(n \log n)$. Every comparison-based sorting algorithm must perform **at least $\Omega(n \log n)$ comparisons in the worst case**.

**Implications.**
- Merge Sort and Heap Sort achieve this optimal bound in all cases.
- Quick Sort achieves $O(n \log n)$ on average but degenerates to $O(n^2)$ in the worst case.
- Bubble, Selection, and Insertion Sorts are asymptotically suboptimal at $O(n^2)$.

Non-comparison sorts (Counting Sort, Radix Sort) **circumvent** this lower bound by exploiting structural properties of the data (integer values with bounded range) rather than relying solely on pairwise comparisons.

---

## Algorithm Steps

### Bubble Sort
1. Traverse left to right, swapping adjacent elements if they are out of order.
2. After each pass, the largest unsorted element settles at the end.
3. Repeat until a pass completes with no swaps (early exit).

### Selection Sort
1. Find the minimum element in the unsorted region.
2. Swap it with the first element of the unsorted region.
3. Advance the boundary by one and repeat.

### Insertion Sort
1. Start with the second element as the key.
2. Shift larger elements rightwards one position at a time.
3. Insert the key into the vacated slot.
4. Advance to the next unsorted element and repeat.

### Merge Sort
1. Recursively divide the array into two halves until each subarray has size 1.
2. Merge two sorted subarrays by repeatedly selecting the smaller front element.
3. Continue merging bottom-up until the full array is assembled.

### Quick Sort
1. Choose the last element as the pivot (Lomuto scheme).
2. Partition: rearrange so elements $<$ pivot precede it and elements $\ge$ pivot follow it.
3. Recursively sort the left and right subarrays.

### Counting Sort
1. Find the minimum and maximum values to determine the range $k$.
2. Count the frequency of each distinct value.
3. Convert counts to prefix sums (cumulative positions).
4. Iterate the input in reverse, placing each element at its correct position using the prefix sums.
5. Copy the sorted output back to the original array.

### Radix Sort
1. Find the maximum value to determine the number of digit positions.
2. For each digit position (LSD first):
   - Perform a stable counting sort on the current digit.
3. After all digit positions are processed, the array is fully sorted.

### Quickselect (Kth Smallest Element)
Quickselect is a selection algorithm to find the $k$-th smallest element in an unordered list. It is related to the Quick Sort sorting algorithm.

1. **Partition:** Similar to Quick Sort, choose a pivot and partition the array.
2. **Select:**
   - If the pivot's final index is $k-1$, the pivot is the $k$-th smallest.
   - If the pivot's final index is $> k-1$, recurse on the left partition.
   - If the pivot's final index is $< k-1$, recurse on the right partition.

**Complexity Analysis:**
- **Best Case:** $O(n)$ — The pivot is always the target.
- **Average Case:** $O(n)$ — On average, we eliminate half the search space in each step.
  - Recurrence: $T(n) = T(n/2) + O(n) = O(n + n/2 + n/4 + \dots) = O(2n) = O(n)$.
- **Worst Case:** $O(n^2)$ — Similar to Quick Sort, if the pivot is always the min/max and the target is at the other end.
- **Space:** $O(1)$ — In-place with tail recursion.

---

## Manual Tracing Examples

### In-Place Quick Sort Partition (Lomuto)
Initial: `[5, 2, 9, 1, 7, 6, 3]` (Pivot: 3)
1. `i = -1`. Compare 5 with 3: `5 > 3`, no swap.
2. Compare 2 with 3: `2 <= 3`, `i = 0`. Swap `arr[0]` (5) with `arr[0]` (5). `[5, 2, 9, 1, 7, 6, 3]`? Wait, swap 2 with 5.
   - Correction: `i` tracks the end of the "less than" part.
   - `j=0 (5)`: `5 > 3`, no swap.
   - `j=1 (2)`: `2 <= 3`, `i++ (0)`, swap `arr[0]`(5) and `arr[1]`(2). `[2, 5, 9, 1, 7, 6, 3]`
   - `j=2 (9)`: `9 > 3`, no swap.
   - `j=3 (1)`: `1 <= 3`, `i++ (1)`, swap `arr[1]`(5) and `arr[3]`(1). `[2, 1, 9, 5, 7, 6, 3]`
   - `j=4, 5`: No swaps.
   - Final: Swap pivot(3) with `arr[i+1]`(9). `[2, 1, 3, 5, 7, 6, 9]`
Result: Pivot 3 at index 2. Left: `[2, 1]`, Right: `[5, 7, 6, 9]`.

### Heap Sort
1. Build a max-heap from the array (heapify all non-leaf nodes).
2. Swap the root (maximum element) with the last unsorted element.
3. Reduce the heap size by one and sift the new root down to restore the heap property.
4. Repeat steps 2–3 until one element remains.
