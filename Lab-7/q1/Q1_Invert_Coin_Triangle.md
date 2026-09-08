# Question 1: Invert the Coin-Triangle

## Algorithm

1.  Represent the centers of the coins as points on a triangular
    lattice.

2.  Let the triangle contain `n` rows, giving `n(n+1)/2` coins.

3.  Consider the possible positions of the inverted triangle on the same
    triangular lattice.

4.  For each possible position, determine the number of coin positions
    common to both the original and inverted triangles.

5.  Calculate the number of coins that must be moved:

    `moves = total coins - overlapping positions`

6.  Choose the position with the maximum overlap.

7.  Move the remaining coins to the corresponding positions of the
    inverted triangle.

8.  The arrangement with maximum overlap gives the minimum number of
    moves.
