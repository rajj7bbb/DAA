# Q6. Reorganise String with K-Distance Apart

## Greedy Idea
At every position, choose the character with the **highest remaining frequency** that is currently allowed.

A max-heap stores available characters by frequency, while a queue stores characters in a cooldown period of `K` positions.

## Algorithm
1. Count the frequency of every character.
2. Insert all characters into a max-heap according to frequency.
3. For each output position:
   - remove the highest-frequency available character;
   - append it to the answer;
   - decrease its frequency;
   - put it into the cooldown queue.
4. Once a character has remained in cooldown for `K` positions, move it back to the max-heap if its frequency is still positive.
5. If the heap becomes empty before the string is completely constructed, return impossible.
6. Otherwise return the rearranged string.

## Complexity Analysis
Let `A` be the alphabet size.

- Frequency counting: `O(n)`
- Each character occurrence causes at most one heap insertion/extraction.
- Heap operation: `O(log A)`

Therefore:

**Total Time Complexity: `O(n log A)`**

For a fixed alphabet such as ASCII (`A <= 256`), this is effectively:

**`O(n)`**

**Space Complexity: `O(n + A)`**

## Key Point
The max-heap handles the greedy frequency choice, while the cooldown queue prevents the same character from being selected too soon.
