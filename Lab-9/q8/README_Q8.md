# Q8. Minimum Number of Meeting Rooms

## Greedy Idea
Sort meetings by their starting time.

Maintain a **min-heap of ending times** of meetings currently occupying rooms.

For each new meeting:
- if the earliest ending meeting has already ended, reuse its room;
- otherwise, another room is required.

The maximum heap size is the answer.

## Algorithm
1. Sort all meetings by start time.
2. Create an empty min-heap.
3. For every meeting `(start, end)`:
   - remove all meetings whose end time is `<= start`;
   - insert the current meeting's end time.
4. Track the maximum heap size.
5. Output that maximum.

## Complexity Analysis
- Sorting meetings: `O(n log n)`
- Each meeting is inserted once: `O(n log n)`
- Each meeting is removed at most once: `O(n log n)`

Therefore:

**Total Time Complexity: `O(n log n)`**

**Space Complexity: `O(n)`**

## Key Point
The min-heap always gives the room that becomes free earliest, so it is the correct room to reuse whenever possible.
