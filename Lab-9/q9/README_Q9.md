# Q9. Hu-Tucker Greedy Algorithm

## Problem
Given ordered weights:

`w1, w2, ..., wn`

construct an optimal **alphabetic binary tree** minimizing:

`Σ wi × depth(i)`

The leaves must remain in their original order.

## Greedy Idea
Unlike ordinary Huffman coding, arbitrary symbols cannot be combined.

Hu-Tucker maintains alphabetic order and repeatedly selects the minimum-cost **compatible adjacent pair** that can be combined without violating the required leaf order.

The combined node receives the sum of the two weights.

## Algorithm — Conceptual Hu-Tucker Procedure
1. Create one node for each weight in its original order.
2. Maintain the alphabetic order.
3. Identify the minimum-cost pair of compatible nodes that can be merged.
4. Merge the selected pair into one internal node.
5. Give the new node weight equal to the sum of its children.
6. Preserve the original left-to-right order.
7. Repeat until one tree remains.
8. Traverse the tree to obtain alphabetic binary codes.

## Complexity Analysis
The optimized Hu-Tucker algorithm can be implemented in:

**Total Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

A straightforward implementation using repeated scans to find the next compatible pair can be slower, typically `O(n^2)`. An interval-DP validator is also possible but is not the Hu-Tucker greedy algorithm.

## Key Point
The essential difference from Huffman coding is the **alphabetic-order constraint**. The symbols cannot be freely rearranged.
