# Q3. Maximum Weight Component with Size Constraints

## Problem
Each vertex has a weight. Edges are inserted sequentially. After each insertion, report the maximum total weight among connected components whose number of vertices is at most `K`.

## Algorithm
1. Initialize each vertex as a separate DSU component.
2. Store each component's size and sum of vertex weights.
3. For every inserted edge `(u, v)`, merge the components if their representatives differ.
4. Scan the vertices to identify DSU representatives.
5. Among representatives whose component size is at most `K`, find the largest component-weight sum and output it. If none qualifies, output `No eligible component`.

## Complexity Analysis
Let `N` be the number of vertices, `M` the number of inserted edges, and `K` the maximum allowed component size.

- **Initialization time:** `O(N)`
- **Each union operation:** `O(α(N))` amortized.
- **Finding the answer after each edge:** `O(N α(N))` in the provided implementation, because it scans all vertices and calls `find`.
- **Total time:** `O(N + M N α(N))`
- **Auxiliary space:** `O(N)`

This is the complexity of the straightforward implementation provided. It is not optimal for large constraints; a more advanced data structure would be needed to avoid scanning every component after every edge.

## Notes
- Vertex weights may be positive, zero, or negative. The implementation tracks whether an eligible component exists rather than assuming the best sum is nonnegative.
- A component is eligible exactly when its size is `≤ K`.
