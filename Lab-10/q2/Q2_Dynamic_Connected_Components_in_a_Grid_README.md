# Q2. Dynamic Connected Components in a Grid

## Problem
An initially empty `R × C` grid receives water-cell activations one at a time. After each activation, output the number of islands. Water cells are connected only horizontally or vertically.

## Algorithm
1. Flatten cell `(r, c)` into the one-dimensional index `r * C + c`.
2. Initialize every cell as inactive and prepare a DSU structure.
3. For each activation:
   - If the cell is already active, do nothing.
   - Otherwise, activate it and increase the island count by one.
   - Check its four neighbours: up, down, left, and right.
   - For every active neighbour in a different DSU component, merge the components and decrease the island count by one.
4. Output the island count after every operation.

## Complexity Analysis
Let `N = R × C` be the number of grid cells and `K` the number of activation operations.

- **Initialization time:** `O(RC)`
- **Work per activation:** at most four neighbour checks and a constant number of DSU operations, `O(α(RC))` amortized.
- **Total time:** `O(RC + K α(RC))`
- **Auxiliary space:** `O(RC)`

Here, `α(RC)` is the inverse Ackermann function.

## Notes
- Input coordinates in the sample implementation are one-based.
- Connectivity is four-directional; diagonal cells are not connected.
- Repeated activation of an already active cell does not increase the island count.
