# Question 4: Security Switches

## Algorithm

1.  Represent each switch configuration as a binary number:

    -   `1` = ON
    -   `0` = OFF

2.  The initial state is:

    `111...111`

3.  The goal state is:

    `000...000`

4.  Treat every possible switch configuration as a state.

5.  Use Breadth-First Search (BFS) starting from the initial state.

6.  For every state, check each switch:

    -   The rightmost switch can always be toggled.
    -   Any other switch can be toggled only if its immediate right
        switch is ON and all switches further right are OFF.

7.  Toggle a legal switch using XOR:

    `newState = state ^ (1 << i)`

8.  If the new state has not been visited, store its parent and the
    switch used, then add it to the queue.

9.  Continue until the all-OFF state is reached.

10. Since BFS explores states in increasing order of moves, the first
    time the all-OFF state is reached gives the minimum number of moves.

11. The minimum number of moves is:

`M(n) = floor(2^(n+1) / 3)`
