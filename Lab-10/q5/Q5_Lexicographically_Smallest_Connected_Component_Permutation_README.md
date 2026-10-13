# Q5. Lexicographically Smallest Connected Component Permutation

## Problem
Given a permutation and an undirected graph, values may be swapped along graph edges any number of times. Find the lexicographically smallest permutation obtainable through these swaps.

## Algorithm
1. Initialize a DSU with one set per vertex.
2. Process every edge and union its endpoints.
3. For each connected component:
   - Collect its vertex indices.
   - Collect the permutation values currently located at those indices.
   - Sort the indices in increasing order.
   - Sort the values in increasing order.
   - Assign the sorted values to the sorted indices.
4. Output the resulting permutation.

Any two vertices in the same connected component can exchange values through a sequence of allowed swaps, so each component's values can be rearranged arbitrarily within that component.

## Complexity Analysis
Let `N` be the number of vertices and `M` the number of edges.

For the straightforward implementation provided:

- **Building DSU:** `O(N + M α(N))`
- **Grouping by repeated full scans:** `O(N² α(N))` in the worst case, because the code scans all vertices for each component and calls `find`.
- **Sorting:** At most `O(N log N)` total across all component index/value lists.
- **Total time:** `O(N² α(N) + M α(N) + N log N)`
- **Auxiliary space:** `O(N)`

The repeated-scan implementation is simple but can be slow for large `N`. If vertices are grouped into components in one pass using lists/buckets, the total can be improved to `O(N log N + M α(N))` time with `O(N)` auxiliary space.
