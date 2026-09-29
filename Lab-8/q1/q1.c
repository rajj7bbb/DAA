#include <stdio.h>
#include <stdlib.h>

int minCoins(int coins[], int n, int V)
{
    int *dp = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = V + 1;

    for (int i = 1; i <= V; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i)
            {
                if (dp[i - coins[j]] + 1 < dp[i])
                    dp[i] = dp[i - coins[j]] + 1;
            }
        }
    }

    int result = (dp[V] > V) ? -1 : dp[V];

    free(dp);
    return result;
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = (int *)malloc(n * sizeof(int));

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int result = minCoins(coins, n, V);

    printf("Minimum number of coins = %d\n", result);

    free(coins);

    return 0;
}