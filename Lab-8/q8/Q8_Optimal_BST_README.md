# Q8 --- Optimal Binary Search Tree (OBST): Complexity Analysis

## Problem

Given `n` sorted keys with successful-search probabilities `p1...pn` and
`n+1` dummy keys with unsuccessful-search probabilities `q0...qn`,
construct an optimal BST with minimum expected search cost.

## DP Representation

We use three tables:

-   `e[i][j]` --- minimum expected search cost for keys `ki...kj`
-   `w[i][j]` --- total probability weight of that interval
-   `root[i][j]` --- root that gives the minimum cost, used for
    reconstruction

The recurrence is:

``` text
e[i][j] =
    min over r from i to j:
    e[i][r-1] + e[r+1][j] + w[i][j]
```

------------------------------------------------------------------------

## Time Complexity Derivation

The algorithm considers all possible intervals of keys.

For an interval of length `L`, there are:

\[ n-L+1 \]

such intervals.

For each interval, all `L` possible roots are tested.

Therefore, the total number of root evaluations is:

\[ `\sum`{=tex}\_{L=1}\^{n}(n-L+1)L \]

Expand:

\[ `\sum`{=tex}\_{L=1}\^{n}(n+1-L)L \]

\[ =(n+1)`\sum`{=tex}*{L=1}\^{n}L-`\sum`{=tex}*{L=1}^{n}L^2 \]

Using:

\[ `\sum`{=tex}\_{L=1}\^{n}L=`\frac{n(n+1)}{2}`{=tex} \]

and:

\[ `\sum`{=tex}\_{L=1}^{n}L^2=`\frac{n(n+1)(2n+1)}{6}`{=tex} \]

the resulting expression has a cubic leading term:

\[ `\Theta`{=tex}(n\^3) \]

Thus:

\[ `\boxed{T(n)=\Theta(n^3)}`{=tex} \]

The weight table can be filled in constant time per interval, so it does
not increase the cubic bound.

If the optimal tree is reconstructed by recursively following the `root`
table, the reconstruction itself visits `O(n)` keys and is dominated by
`O(n³)`.

------------------------------------------------------------------------

## Space Complexity Derivation

The algorithm stores three `n x n`-type tables:

``` text
e[][]     -> O(n²)
w[][]     -> O(n²)
root[][]  -> O(n²)
```

Therefore:

\[ O(n^2)+O(n^2)+O(n^2)=O(n^2) \]

Hence:

\[ `\boxed{S(n)=O(n^2)}`{=tex} \]

## Final Answer

-   **Time Complexity:** `O(n³)`
-   **Auxiliary Space Complexity:** `O(n²)`
