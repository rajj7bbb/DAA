#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;

            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int length = dp[m][n];

    char *lcs = (char *)malloc((length + 1) * sizeof(char));
    lcs[length] = '\0';

    int i = m;
    int j = n;
    int k = length - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[k] = X[i - 1];
            i--;
            j--;
            k--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("Length of LCS = %d\n", length);
    printf("LCS = %s\n", lcs);

    free(lcs);

    for (int i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);
}

int main()
{
    char X[100], Y[100];

    printf("Enter first sequence: ");
    scanf("%s", X);

    printf("Enter second sequence: ");
    scanf("%s", Y);

    findLCS(X, Y);

    return 0;
}
