# Q1 --- Minimum Coin Change: Complexity Analysis

## Problem

Given `n` coin denominations and a target amount `V`, find the minimum
number of coins needed to make `V`. An unlimited number of every
denomination is available.

## DP Representation

Let:

`dp[i]` = minimum number of coins required to make amount `i`.

For every amount `i`, we examine every coin denomination `C[j]`.

The recurrence is:

``` text
dp[i] = min(dp[i], dp[i - C[j]] + 1)
```

whenever `C[j] <= i`.

------------------------------------------------------------------------

## Time Complexity Derivation

There are `V` DP states:

``` text
dp[0], dp[1], ..., dp[V]
```

For every state `i`, we check all `n` coin denominations.

Therefore:

``` text
Number of states = V
Work per state = n
```

Hence,

``` text
T(V,n) = n + n + ... + n       (V times)
       = nV
```

Therefore:

\[ `\boxed{T(n,V)=O(nV)}`{=tex} \]

The initialization of the DP array takes `O(V)` time, which is dominated
by `O(nV)` when `n >= 1`.

If the final result is simply `dp[V]`, retrieving it takes `O(1)`.

### Final Time Complexity

\[ `\boxed{O(nV)}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity Derivation

We store one DP array:

``` text
dp[0 ... V]
```

It contains `V + 1` entries.

Therefore:

``` text
Space = V + 1
```

Hence:

\[ `\boxed{O(V)}`{=tex} \]

The input coin array requires `O(n)` space, so including input storage
the total is `O(n + V)`. The usual auxiliary-space complexity of the DP
algorithm is `O(V)`.

## Final Answer

-   **Time Complexity:** `O(nV)`
-   **Auxiliary Space Complexity:** `O(V)`
