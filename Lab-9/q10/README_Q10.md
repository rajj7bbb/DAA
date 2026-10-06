# Q10. Greedy Superstring Conjecture — Open Problem

## Important Note
This question is explicitly an **open/unsolved problem**. Do not claim that the greedy algorithm is always optimal or that its conjectured approximation guarantee has been proven.

The required response is the greedy algorithm/approach.

## Greedy Idea
Repeatedly select the pair of strings having the **maximum suffix-prefix overlap**.

For strings `A` and `B`, the overlap is the largest `k` such that:

`suffix_k(A) = prefix_k(B)`

Then merge them as:

`A + B[k ... end]`

This process is repeated until only one string remains.

## Algorithm
1. Start with the set of strings `S`.
2. While more than one string remains:
   - examine every ordered pair `(A, B)`;
   - calculate the longest suffix of `A` matching a prefix of `B`;
   - choose the pair with maximum overlap;
   - merge the pair;
   - remove the two original strings;
   - insert the merged string.
3. Return the final string.

## Pseudocode

```text
GreedySuperstring(S):

    while |S| > 1:

        bestOverlap = -1

        for every ordered pair (A, B):
            k = longest suffix of A
                matching prefix of B

            if k > bestOverlap:
                save (A, B, k)

        C = A + B[k ... end]

        remove A and B from S
        insert C into S

    return the only remaining string
```

## Complexity Analysis of the Naive Implementation
Let:
- `n` = number of input strings
- `L` = maximum string length

For one greedy iteration:
- number of ordered pairs = `O(n^2)`
- computing an overlap naively = `O(L)`

So one iteration costs:

`O(n^2 L)`

There can be up to `n - 1` iterations.

Therefore the straightforward implementation has:

**Total Time Complexity: `O(n^3 L)`**

**Space Complexity: `O(nL)`** in the worst case for storing the strings and intermediate merged strings.

## Important Conclusion
The greedy maximum-overlap method is a useful heuristic, but the **Greedy Superstring Conjecture is not a solved theorem**. The question asks for exploration of the conjecture rather than a proven optimal algorithm.
