# Q1. Online Graph Bipartiteness Test

## Problem
An undirected graph has `V` vertices. Edges arrive one at a time. After each edge is added, determine whether the graph remains bipartite. A graph is bipartite if its vertices can be divided into two sets so that every edge joins vertices in different sets.

## Algorithm
1. Initialize a Disjoint Set Union (DSU) structure with every vertex in its own set.
2. Store a parity value for each vertex, representing its color relative to its DSU representative.
3. For each new edge `(u, v)`:
   - Find the representatives of `u` and `v`.
   - If they are already in the same set, check whether their parities differ. If they do not, the new edge creates an odd-cycle contradiction.
   - Otherwise, merge the two sets while enforcing opposite colors for `u` and `v`.
4. Once a contradiction is found, the graph is no longer bipartite; later edges cannot restore bipartiteness.

## Complexity Analysis
Let `V` be the number of vertices and `E` the number of inserted edges.

- **Initialization time:** `O(V)`
- **Time per edge:** `O(α(V))` amortized, using path compression and union by size/rank.
- **Total time:** `O(V + E α(V))`
- **Auxiliary space:** `O(V)`

Here, `α(V)` is the inverse Ackermann function, which grows so slowly that it is effectively constant for practical input sizes.

## Notes
- Vertices in the sample implementation are numbered from `1` through `V`.
- Each edge is processed in arrival order.
- A self-loop immediately makes the graph non-bipartite.
