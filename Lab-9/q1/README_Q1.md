# Q1. Fractional Knapsack with Deterioration Rate

## Greedy Idea
For item `i`, the value density at time `t` is:

`d_i(t) = v_i / w_i - λ_i t`

Because an item's density decreases with time according to its deterioration rate, the greedy schedule prioritizes items with larger deterioration rate, so that rapidly deteriorating value is consumed earlier. After choosing the order, fill the knapsack fractionally.

## Algorithm
1. Read `n`, capacity `W`, and `(v_i, w_i, λ_i)` for every item.
2. Sort items in decreasing order of deterioration rate `λ_i`.
3. Start with `t = 0` and remaining capacity `W`.
4. For each item, compute its current density `v_i/w_i - λ_i t`.
5. Take the maximum possible fraction of that item.
6. Add `quantity × current_density` to the total value.
7. Increase `t` by the amount consumed.
8. Stop when capacity is full or all useful items are processed.

## Complexity Analysis
- Sorting: `O(n log n)`
- Single traversal: `O(n)`
- **Total Time Complexity: `O(n log n)`**
- **Space Complexity: `O(n)`** for storing the items.

## Key Point
The dominant operation is sorting; therefore the overall complexity is **O(n log n)**.
