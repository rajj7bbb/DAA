# Question 3: Reve's Puzzle

## Algorithm

1.  Let `T[n]` denote the minimum number of moves required to transfer
    `n` disks using four pegs.

2.  Set:

    `T[0] = 0`

3.  For `n` disks, divide the disks into two groups:

    -   `k` smallest disks
    -   `n-k` largest disks

4.  Move the `k` smallest disks to an auxiliary peg using the four-peg
    solution.

5.  Move the remaining `n-k` largest disks to the destination using the
    standard three-peg Tower of Hanoi. This requires:

    `2^(n-k) - 1`

    moves.

6.  Move the `k` smallest disks from the auxiliary peg to the
    destination using the four-peg solution.

7.  For every possible `k`, calculate:

    `2*T[k] + 2^(n-k) - 1`

8.  Choose the value of `k` that gives the minimum.

9.  Therefore:

    `T[n] = min(2*T[k] + 2^(n-k) - 1)`

    for `0 <= k < n`.

10. Store the optimal `k` in a `split[]` array.

11. For 8 disks, the optimal split is `k = 4`, giving:

`T[8] = 2*T[4] + 2^4 - 1 = 33`

12. Therefore, 8 disks require **33 moves**.
