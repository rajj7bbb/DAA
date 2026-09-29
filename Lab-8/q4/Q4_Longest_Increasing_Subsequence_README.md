# Q4 --- Longest Increasing Subsequence (LIS): Complexity Analysis

## Problem

Given an array of `n` integers, find the length of the longest
subsequence whose elements are strictly increasing.

## DP Representation

Let:

`dp[i]` = length of the longest strictly increasing subsequence ending
at index `i`.

Initially:

``` text
dp[i] = 1
```

because every individual element forms an increasing subsequence of
length 1.

For each `i`, examine every earlier index `j`.

If:

``` text
A[j] < A[i]
```

then:

``` text
dp[i] = max(dp[i], dp[j] + 1)
```

------------------------------------------------------------------------

## Time Complexity Derivation

For each `i`, the algorithm checks all previous positions:

``` text
i = 0  -> 0 comparisons
i = 1  -> 1 comparison
i = 2  -> 2 comparisons
...
i = n-1 -> n-1 comparisons
```

Therefore the total number of comparisons is:

\[ 0+1+2+`\cdots`{=tex}+(n-1) \]

Using the arithmetic-series formula:

\[ `\frac{n(n-1)}{2}`{=tex} \]

Thus:

\[ T(n)=`\Theta`{=tex}(n\^2) \]

The final scan for the maximum of `dp` takes `O(n)`, which is dominated
by `O(n²)`.

Therefore:

\[ `\boxed{T(n)=O(n^2)}`{=tex} \]

and more precisely the nested-loop portion is `Theta(n²)`.

------------------------------------------------------------------------

## Space Complexity Derivation

We store:

``` text
dp[0 ... n-1]
```

which contains `n` values.

Therefore:

\[ `\boxed{O(n)}`{=tex} \]

The input array itself requires `O(n)` storage if counted.

## Final Answer

-   **Time Complexity:** `O(n²)`
-   **Auxiliary Space Complexity:** `O(n)`
