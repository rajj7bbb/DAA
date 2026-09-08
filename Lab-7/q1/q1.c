#include <stdio.h>

long long minMoves(int n)
{
    long long q = n / 3;
    int r = n % 3;

    if (r == 0)
        return q * (3 * q + 1) / 2;

    else if (r == 1)
        return 3 * q * (q + 1) / 2;

    else
        return (q + 1) * (3 * q + 2) / 2;
}

int main()
{
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    printf("Minimum number of moves = %lld\n", minMoves(n));

    return 0;
}