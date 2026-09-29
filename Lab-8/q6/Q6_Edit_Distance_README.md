# Q6 --- Edit Distance with Traceback: Complexity Analysis

## Problem

Given strings `A` and `B` of lengths `m` and `n`, find the minimum
number of insertions, deletions, and substitutions required to transform
`A` into `B`, and reconstruct the operations.

## DP Representation

Let:

`dp[i][j]` = minimum edit distance between the first `i` characters of
`A` and the first `j` characters of `B`.

If the characters match:

``` text
dp[i][j] = dp[i-1][j-1]
```

Otherwise:

``` text
dp[i][j] = 1 + min(
    dp[i-1][j],      // deletion
    dp[i][j-1],      // insertion
    dp[i-1][j-1]     // substitution
)
```

------------------------------------------------------------------------

## Time Complexity Derivation

The DP table has:

``` text
(m + 1) x (n + 1)
```

cells.

Thus the number of cells is:

\[ (m+1)(n+1)=O(mn) \]

Each cell performs constant work: character comparison and a minimum
over three values.

Therefore:

\[ `\boxed{T_{DP}(m,n)=O(mn)}`{=tex} \]

### Traceback Complexity

Traceback starts at `dp[m][n]`.

At each step, at least one of `i` or `j` decreases. Therefore there can
be at most:

\[ m+n \]

traceback steps.

So:

\[ T\_{traceback}=O(m+n) \]

Combining both:

\[ O(mn)+O(m+n)=O(mn) \]

Therefore:

\[ `\boxed{T(m,n)=O(mn)}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity Derivation

The DP table contains:

\[ (m+1)(n+1) \]

entries.

Hence:

\[ `\boxed{O(mn)}`{=tex} \]

The traceback output may contain `O(m+n)` operations, but this does not
change the asymptotic space used by the full DP table.

## Final Answer

-   **Time Complexity:** `O(mn)`
-   **Auxiliary Space Complexity:** `O(mn)`
