# Q5. Candy Distribution — Bi-directional Slope Greedy

## Greedy Idea
Each child initially gets one candy.

The condition must be satisfied from both directions:
- a child with a higher rating than the left neighbor needs more candies;
- a child with a higher rating than the right neighbor also needs more candies.

Use two greedy passes.

## Algorithm
### Left-to-right pass
Set every value of `left[]` to `1`.

For `i = 1 ... n-1`:
- if `rating[i] > rating[i-1]`, set `left[i] = left[i-1] + 1`.

### Right-to-left pass
Set every value of `right[]` to `1`.

For `i = n-2 ... 0`:
- if `rating[i] > rating[i+1]`, set `right[i] = right[i+1] + 1`.

For every child:

`candy[i] = max(left[i], right[i])`

Add all candy values.

## Complexity Analysis
- Left-to-right pass: `O(n)`
- Right-to-left pass: `O(n)`
- Final summation: `O(n)`

Therefore:

**Total Time Complexity: `O(n)`**

**Space Complexity: `O(n)`**

## Key Point
The `max(left[i], right[i])` operation ensures that both neighboring constraints are satisfied.
