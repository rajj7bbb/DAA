# Q4. Minimum Cost to Connect Sticks

## Greedy Idea
Always connect the **two shortest available sticks**.

If sticks of lengths `x` and `y` are connected, the cost is `x + y`, and the resulting stick has length `x + y`.

A min-heap efficiently gives the two smallest sticks.

## Algorithm
1. Insert all stick lengths into a min-heap.
2. While more than one stick remains:
   - extract the two smallest lengths `x` and `y`;
   - calculate `sum = x + y`;
   - add `sum` to the total cost;
   - insert `sum` back into the min-heap.
3. Output the total cost.

## Complexity Analysis
There are exactly `n - 1` connections.

Each extraction/insertion takes `O(log n)`.

Therefore:

**Total Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

## Key Point
The two smallest sticks must be joined first because a newly formed stick may participate in later joins and therefore its length can contribute to the cost multiple times.
