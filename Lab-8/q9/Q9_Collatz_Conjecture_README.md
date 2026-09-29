# Q9 --- Collatz Conjecture: Complexity Analysis

## Problem

For a positive integer `n`, repeatedly apply:

\[ T(n)=
```{=tex}
\begin{cases}
n/2, & n\text{ is even}\\
3n+1, & n\text{ is odd}
\end{cases}
```
\]

until the trajectory reaches `1`.

The assignment asks for simulation of a user-provided starting value and
analysis over an interval `[a,b]`.

## Important Mathematical Point

The Collatz Conjecture is still unproved in general. Therefore, the
program is a computational experiment: it can simulate specified
starting values, but it does not prove that every positive integer
eventually reaches `1`.

------------------------------------------------------------------------

## Time Complexity for One Starting Value

Let:

`L(n)` = number of Collatz steps taken by starting value `n` before
reaching `1`.

The program performs one constant-time parity check and arithmetic
update for each step.

Therefore:

\[ T(n)=c_1L(n)+c_2 \]

for constants `c1` and `c2`.

Hence:

\[ `\boxed{T(n)=O(L(n))}`{=tex} \]

There is no known general closed-form bound for `L(n)` that would turn
this into a simple polynomial function of `n` for all positive integers.

------------------------------------------------------------------------

## Space Complexity for One Starting Value

If the program only keeps:

``` text
current
steps
maxValue
```

and prints the trajectory directly, it does not need to store the entire
trajectory.

Therefore the auxiliary space is constant:

\[ `\boxed{S(n)=O(1)}`{=tex} \]

If the complete trajectory were stored in an array, the space would
instead depend on its length and could be `O(L(n))`.

------------------------------------------------------------------------

## Complexity for an Interval \[a,b\]

Let:

``` text
L(x) = number of steps for starting value x
```

The program simulates every starting value:

``` text
a, a+1, ..., b
```

There are:

\[ b-a+1 \]

starting values.

The total number of Collatz steps is:

\[ `\sum`{=tex}\_{x=a}\^{b}L(x) \]

Therefore:

\[ `\boxed{
T(a,b)=O\left(\sum_{x=a}^{b}L(x)\right)
}`{=tex} \]

If:

\[ L\_{`\max`{=tex}}=`\max`{=tex}\_{a`\le `{=tex}x`\le `{=tex}b}L(x) \]

then:

\[ `\sum`{=tex}*{x=a}\^{b}L(x) `\le`{=tex} (b-a+1)L*{`\max`{=tex}} \]

so an upper-bound expression is:

\[ `\boxed{
T(a,b)=O((b-a+1)L_{\max})
}`{=tex} \]

------------------------------------------------------------------------

## Space Complexity for an Interval

If each trajectory is processed one at a time and only its current
statistics are stored, the same constant amount of working memory is
reused.

Therefore:

\[ `\boxed{S(a,b)=O(1)}`{=tex} \]

excluding the space required by printed output.

------------------------------------------------------------------------

## Final Answer

### One starting value

-   **Time:** `O(L(n))`
-   **Auxiliary Space:** `O(1)`

### Interval `[a,b]`

-   **Time:** `O(sum L(x))` for `x = a...b`
-   **Equivalent upper bound:** `O((b-a+1)Lmax)`
-   **Auxiliary Space:** `O(1)`

where `L(x)` is the observed number of Collatz steps for starting value
`x`.
