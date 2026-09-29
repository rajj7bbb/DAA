# Q3 --- Longest Common Subsequence (LCS): Complexity Analysis

## Problem

Given two sequences `X` and `Y` of lengths `m` and `n`, find the length
of their longest common subsequence and reconstruct an actual LCS.

## DP Representation

Define:

`dp[i][j]` = length of the LCS of the first `i` elements of `X` and the
first `j` elements of `Y`.

The recurrence is:

``` text
if X[i-1] == Y[j-1]:
    dp[i][j] = dp[i-1][j-1] + 1
else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

------------------------------------------------------------------------

## Time Complexity Derivation

The DP table has dimensions:

``` text
(m + 1) x (n + 1)
```

Therefore, the number of DP cells is:

``` text
(m + 1)(n + 1)
```

For every cell, only constant work is performed: comparison, addition,
and/or maximum.

Thus:

``` text
T(m,n) = (m+1)(n+1) * O(1)
       = O(mn)
```

### Traceback Cost

To reconstruct the LCS, we start at `dp[m][n]` and move either:

-   diagonally,
-   upward, or
-   leftward.

At least one index decreases at every step, so there are at most `m + n`
traceback steps.

Thus:

``` text
Traceback = O(m+n)
```

Since:

``` text
O(mn) + O(m+n) = O(mn)
```

for nontrivial `m,n`, the overall time complexity remains:

\[ `\boxed{O(mn)}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity Derivation

The DP table stores `(m+1)(n+1)` values:

\[ (m+1)(n+1)=O(mn) \]

The reconstructed LCS uses at most `O(min(m,n))` additional space, which
does not exceed the DP-table order.

Therefore:

\[ `\boxed{O(mn)}`{=tex} \]

## Final Answer

-   **Time Complexity:** `O(mn)`
-   **Auxiliary Space Complexity:** `O(mn)`
