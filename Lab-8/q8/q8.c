#include <stdio.h>
#include <stdlib.h>

#define INF 999999

void printTree(int root[][100], int i, int j)
{
    if (i > j)
        return;

    int r = root[i][j];

    printf("k%d is root of keys k%d to k%d\n", r, i, j);

    printTree(root, i, r - 1);
    printTree(root, r + 1, j);
}

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    double e[100][100];
    double w[100][100];
    int root[100][100];

    printf("Enter successful search probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter unsuccessful search probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    /*
       Base case:
       Empty subtrees
    */

    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /*
       Calculate DP tables
    */

    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = INF;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++)
            {
                double cost =
                    e[i][r - 1] +
                    e[r + 1][j] +
                    w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.2lf\n", e[1][n]);

    printf("\nOptimal BST Structure:\n");

    printTree(root, 1, n);

    free(p);
    free(q);

    return 0;
}