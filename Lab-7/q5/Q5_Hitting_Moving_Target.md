# Question 5: Hitting a Moving Target

## Algorithm

1.  Number the hiding spots from `1` to `n`.

2.  The target must move to an adjacent position after every shot.

3.  If `n = 2`, shoot the same position twice.

4.  If `n` is even:

    -   Shoot positions:

        `2, 3, ..., n-1`

    -   Then shoot in reverse:

        `n-1, n-2, ..., 2`

5.  If `n` is odd:

    -   Shoot positions:

        `2, 3, ..., n-1`

    -   Repeat the same sequence:

        `2, 3, ..., n-1`

6.  The first sweep forces the target into a predictable parity class of
    positions.

7.  The second sweep guarantees that the target will be hit.

8.  Therefore, a guaranteed strategy exists for every `n > 1`.

9.  For `n > 2`, the number of shots is:

    `2n - 4`
