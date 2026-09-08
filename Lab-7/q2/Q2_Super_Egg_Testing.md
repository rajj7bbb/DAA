# Question 2: Super Egg Testing Experiment

## Algorithm

1.  Let `dp[e]` represent the maximum number of floors that can be
    tested using `e` eggs and the current number of drops.

2.  Initially set `dp[e] = 0` for every number of eggs.

3.  Set `drops = 0`.

4.  Increase the number of drops by 1.

5.  Update the DP array from right to left using:

    `dp[e] = dp[e] + dp[e-1] + 1`

6.  Continue until:

    `dp[E] >= F`

    where `E` is the number of eggs and `F` is the number of floors.

7.  The current value of `drops` is the minimum number of drops
    guaranteed to determine the safe floor.

8.  For `E = 2` and `F = 100`, the answer is **14 drops**.
