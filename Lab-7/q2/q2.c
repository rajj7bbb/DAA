#include <stdio.h>

int minDrops(int E, int F)
{
    int dp[E + 1];
    int drops = 0;

    for (int e = 0; e <= E; e++)
        dp[e] = 0;

    while (dp[E] < F)
    {
        drops++;

        for (int e = E; e >= 1; e--)
        {
            dp[e] = dp[e] + dp[e - 1] + 1;
        }
    }

    return drops;
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    printf("Minimum number of drops = %d\n",
           minDrops(E, F));

    return 0;
}