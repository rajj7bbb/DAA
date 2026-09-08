#include <stdio.h>
#include <limits.h>

long long power2(int n)
{
    return 1LL << n;
}

void solve(int n)
{
    long long dp[n + 1];
    int split[n + 1];

    dp[0] = 0;
    split[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        for (int k = 0; k < i; k++)
        {
            long long moves =
                2 * dp[k] + power2(i - k) - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("Minimum number of moves = %lld\n", dp[n]);

    printf("\nOptimal splits:\n");

    for (int i = 1; i <= n; i++)
    {
        printf("n = %d : k = %d, moves = %lld\n",
               i, split[i], dp[i]);
    }
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    solve(n);

    return 0;
}