# Q5 --- Maximum Sum Increasing Subsequence (MSIS): Complexity Analysis

## Problem

Given an array of `n` positive integers, find the maximum possible sum
of a strictly increasing subsequence.

## DP Representation

Let:

`dp[i]` = maximum sum of a strictly increasing subsequence ending at
`A[i]`.

Initially:

``` text
dp[i] = A[i]
```

because the subsequence containing only `A[i]` has sum `A[i]`.

For every previous position `j`:

``` text
if A[j] < A[i]:
    dp[i] = max(dp[i], dp[j] + A[i])
```

------------------------------------------------------------------------

## Time Complexity Derivation

For each index `i`, all previous indices `j < i` are examined.

The number of comparisons is:

\[ 0+1+2+`\cdots`{=tex}+(n-1) \]

Using:

\[ `\sum`{=tex}\_{i=0}\^{n-1} i = `\frac{n(n-1)}{2}`{=tex} \]

we get:

\[ T(n)=`\Theta`{=tex}(n\^2) \]

The final scan to find the maximum sum requires `O(n)` time and is
dominated by `O(n²)`.

Therefore:

\[ `\boxed{T(n)=O(n^2)}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity Derivation

The algorithm stores one DP array:

``` text
dp[0 ... n-1]
```

so it requires `n` entries.

Therefore:

\[ `\boxed{O(n)}`{=tex} \]

## Final Answer

-   **Time Complexity:** `O(n²)`
-   **Auxiliary Space Complexity:** `O(n)`
