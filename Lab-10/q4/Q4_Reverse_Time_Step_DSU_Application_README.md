# Q4. Reverse Time-Step DSU Application

## Problem
Given a weighted, undirected graph and a permutation specifying the order in which vertices are deleted, determine the maximum total vertex weight among connected components of the remaining graph at each relevant time step.

## Algorithm
1. Read the graph, vertex weights, and deletion order.
2. Start with all vertices inactive, corresponding to the graph after all vertices have been deleted.
3. Process the deletion order in reverse, activating one vertex at a time.
4. When a vertex is activated, initialize its component sum to its weight.
5. Merge it with every active neighbour using DSU, updating component sizes and sums.
6. Track the maximum component weight after each activation.
7. Map the recorded reverse-time results to the required forward-time deletion answers. Check the exact statement's indexing convention before printing.

## Complexity Analysis
Let `N` be the number of vertices and `M` the number of edges.

- **Initialization time:** `O(N + M)` for arrays and adjacency lists.
- **Each vertex activation:** `O(1)` apart from neighbour processing.
- **All DSU operations:** `O((N + M) α(N))` amortized, because each vertex is activated once and each edge is examined a constant number of times.
- **Total time:** `O((N + M) α(N))`
- **Auxiliary space:** `O(N + M)`

Here, `α(N)` is the inverse Ackermann function.

## Important Implementation Note
The sample implementation records the maximum component sum after each reverse activation. If the required output is the graph state after each forward deletion, the answer array may need an index shift, and the empty-graph state may need special handling. Follow the precise statement's definition of “after each deletion.” The simple `best = 0` initialization also assumes nonnegative vertex weights; for arbitrary signed weights, initialize the maximum according to the problem's required empty-graph convention.
