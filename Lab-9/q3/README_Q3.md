# Q3. Minimum Initial Fuel (Reverse Greedy)

## Greedy Idea
Whenever the vehicle cannot reach the next required point with its current fuel, use fuel from the **largest previously reachable station**.

A max-heap stores the fuel amounts of all stations that have already become reachable.

Choosing the largest available fuel gives the greatest increase in range per refueling stop.

## Algorithm
1. Sort all stations by distance from the origin.
2. Keep a max-heap of fuel amounts from reachable stations.
3. Move through the stations in increasing distance order.
4. Add every station that can currently be reached to the max-heap.
5. If the destination/next station cannot be reached:
   - remove the largest fuel amount from the heap;
   - add it to the current fuel;
   - increase the number of stops.
6. If the heap is empty when more fuel is required, the destination is unreachable.
7. Continue until the target distance `D` is reached.

## Complexity Analysis
- Sorting stations: `O(n log n)`
- Every station is inserted into the heap at most once: `O(n log n)`
- Every selected refueling amount is removed at most once: `O(n log n)`

Therefore:

**Total Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

## Key Point
The greedy choice is always the **largest fuel amount among stations already reachable**.
