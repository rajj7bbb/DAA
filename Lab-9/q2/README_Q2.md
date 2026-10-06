# Q2. Huffman Coding

## Greedy Idea
Huffman coding repeatedly combines the **two symbols/nodes with the smallest frequencies**. The combined node is inserted back into a min-heap.

This produces a prefix-free binary tree with minimum expected code length.

## Algorithm
1. Create one node for each symbol and its frequency.
2. Insert all nodes into a min-heap.
3. Remove the two nodes with minimum frequency.
4. Create a new node whose frequency is their sum.
5. Make the two removed nodes its children.
6. Insert the new node into the min-heap.
7. Repeat until only one node remains.
8. Traverse the tree: left edge = `0`, right edge = `1`.
9. For a canonical codebook, sort symbols by `(code length, symbol)` and assign canonical binary codes.

## Complexity Analysis
There are `n - 1` merge operations.

Each extraction/insertion in the min-heap costs `O(log n)`.

- Building the heap: `O(n)` with heapify, or `O(n log n)` with repeated insertion.
- `n - 1` merge steps: `O(n log n)`
- Tree traversal: `O(n)` apart from output length.

**Total Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

## Key Point
The min-heap is the main data structure responsible for the `O(log n)` cost per greedy merge.
