#include <stdio.h>
#include <limits.h>

#define MAX 100

void printParenthesis(int s[MAX][MAX], int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printParenthesis(s, i, s[i][j]);

    printf(" x ");

    printParenthesis(s, s[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[MAX];

    printf("Enter %d dimensions:\n", n + 1);

    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    int m[MAX][MAX];
    int s[MAX][MAX];

    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           m[1][n]);

    printf("Optimal parenthesization = ");

    printParenthesis(s, 1, n);

    printf("\n");

    return 0;
}