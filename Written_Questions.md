# Data Structures: Written & Conceptual Questions

This file contains common conceptual questions and "written" exercises found in exams and lecture materials.

## Linear Structures

### Q1: ArrayList vs. LinkedList
Describe the primary differences between an `ArrayList` and a `LinkedList` in terms of memory allocation, random access, and insertion/deletion at the front.

### Q2: Stack Applications
Which data structure is most appropriate for implementing a "Parentheses Checker" in an IDE? Explain why.

### Q3: Circular Queue Logic
Explain the "wrap-around" logic in a Circular Queue implemented with an array. Why is it preferred over a standard array-based queue?

### Q4: Postfix Evaluation
Show the step-by-step stack updates used to calculate the value of the following postfix expression: `8 5 3 * + 8 2 / -`.

## Tree Structures

### Q5: Heap Representation
Why is a binary heap typically implemented using a linear array rather than linked nodes? How are children's indices calculated?

### Q6: AVL Tree Balancing
What is the "Height Bound" of an AVL tree with $n$ nodes? Why is this bound important for time complexity?

### Q7: BST Deletion
In a BST deletion where the target node has two children, what are the two possible replacement nodes? Describe how to find each.

### Q8: BST vs. Hash Table
Compare a BST and a Hash Table for the `search` operation. In what scenario would a BST be preferred?

## Sorting & Complexity

### Q9: Sorting Lower Bound
State the theorem regarding the lower bound of comparison-based sorting algorithms. Briefly explain the logic using the "Decision Tree" model.

### Q10: Quickselect Average Case
What is the average-case time complexity of the Quickselect algorithm (finding the $k$-th smallest element)? How does it differ from Quick Sort's average case?

### Q11: Stability in Sorting
Define "Stability" in the context of sorting algorithms. Name one stable and one unstable sorting algorithm.

## Graphs

### Q12: Graph vs. Tree
Define a "Tree" in terms of Graph Theory. What conditions must a graph satisfy to be considered a tree?

### Q13: Traversal Data Structures
Which data structures are required to implement Breadth-First Search (BFS) and Depth-First Search (DFS) iteratively?

## Recursion

### Q14: Recursion Depth
What is the primary risk of using deep recursion in algorithms like DFS or Quick Sort? How can it be mitigated?
