# Q2 --- Coin Change: Total Number of Ways: Complexity Analysis

## Problem

Given `n` distinct coin denominations and target amount `V`, find the
number of different combinations that make `V`. Unlimited copies of
every coin are available and order does not matter.

## DP Representation

Let:

`dp[j]` = number of combinations that make amount `j` using the coin
denominations processed so far.

Initialize:

``` text
dp[0] = 1
```

Then process each coin using:

``` text
for each coin:
    for j = coin to V:
        dp[j] += dp[j - coin]
```

The coin loop is outermost, which prevents different orders of the same
combination from being counted separately.

------------------------------------------------------------------------

## Time Complexity Derivation

There are `n` coin denominations.

For each coin, the inner loop can run from its value up to `V`, and
therefore performs at most `V` iterations.

Thus the total number of iterations is at most:

``` text
V + V + ... + V       (n times)
```

So:

``` text
T(n,V) <= nV
```

Therefore:

\[ `\boxed{T(n,V)=O(nV)}`{=tex} \]

The initialization takes `O(V)` time and does not change the final
bound.

## Space Complexity Derivation

We use a one-dimensional array:

``` text
dp[0 ... V]
```

which contains `V + 1` entries.

Therefore:

\[ `\boxed{O(V)}`{=tex} \]

If the input array of `n` coins is also counted, total storage is
`O(n + V)`.

## Final Answer

-   **Time Complexity:** `O(nV)`
-   **Auxiliary Space Complexity:** `O(V)`
