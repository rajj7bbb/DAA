# Q7. Minimise Deviation in Array

## Greedy Idea
First make every odd number even by multiplying it by `2`.

After this transformation, the only useful operation for reducing the maximum is dividing an even number by `2`.

Therefore:
- maintain all current values in a **max-heap**;
- repeatedly reduce the current maximum;
- stop when the current maximum becomes odd.

The minimum value must also be tracked because the deviation is:

`max(A) - min(A)`.

## Algorithm
1. Read all elements.
2. If an element is odd, multiply it by `2`.
3. Insert all values into a max-heap.
4. Find the initial minimum.
5. Set `answer = max - min`.
6. Repeatedly:
   - remove the current maximum;
   - update `answer`;
   - if the maximum is odd, stop;
   - divide it by `2`;
   - update the minimum if necessary;
   - insert the reduced value back into the heap.
7. Output `answer`.

## Complexity Analysis
Let `M` be the maximum value after the initial doubling.

- Building/initializing heap: `O(n log n)` with repeated insertion, or `O(n)` with heapify.
- Each division creates one heap update.
- The number of useful divisions is `O(log M)` per element in the worst case.

Thus a safe bound is:

**Total Time Complexity: `O(n log n log M)`**

**Space Complexity: `O(n)`**

## Key Point
The max-heap makes it possible to always process the largest value, which is the only value whose reduction can decrease the current deviation.
