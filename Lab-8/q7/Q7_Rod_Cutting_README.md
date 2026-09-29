# Q7 --- Rod Cutting with Reconstruction: Complexity Analysis

## Problem

Given a rod of length `n` and a price array `P`, determine:

1.  The maximum revenue obtainable by cutting the rod.
2.  The exact piece lengths that produce the maximum revenue.

## DP Representation

Let:

`dp[i]` = maximum revenue obtainable from a rod of length `i`.

For each possible first piece length `j`:

``` text
dp[i] = max(dp[i], price[j] + dp[i-j])
```

We also store:

``` text
cut[i] = first piece length used in the optimal solution for length i
```

This allows reconstruction.

------------------------------------------------------------------------

## Time Complexity Derivation

For every rod length `i`, we try every possible first cut:

``` text
i = 1  -> 1 choice
i = 2  -> 2 choices
...
i = n  -> n choices
```

Therefore, the total number of candidate cuts is:

\[ 1+2+`\cdots`{=tex}+n \]

Using the arithmetic-series formula:

\[ `\frac{n(n+1)}{2}`{=tex} \]

Thus:

\[ T(n)=`\Theta`{=tex}(n\^2) \]

### Reconstruction Cost

After computing the DP table, reconstruction repeatedly subtracts the
selected piece length:

``` text
length = length - cut[length]
```

Each iteration removes at least one unit of rod length, so there are at
most `n` iterations.

Therefore:

\[ T\_{reconstruction}=O(n) \]

The total is:

\[ O(n^2)+O(n)=O(n^2) \]

Hence:

\[ `\boxed{T(n)=O(n^2)}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity Derivation

The algorithm stores:

``` text
price[0...n]  -> O(n)
dp[0...n]     -> O(n)
cut[0...n]    -> O(n)
```

Thus:

\[ O(n)+O(n)+O(n)=O(n) \]

Therefore:

\[ `\boxed{O(n)}`{=tex} \]

## Final Answer

-   **Time Complexity:** `O(n²)`
-   **Auxiliary Space Complexity:** `O(n)`
