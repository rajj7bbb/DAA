#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 0;
    }

    int maxShots = 2 * n;

    int *shots = malloc(maxShots * sizeof(int));
    int count = 0;


    if (n == 2)
    {
        shots[count++] = 1;
        shots[count++] = 1;
    }
    else if (n % 2 == 0)
    {
  
        for (int i = 2; i <= n - 1; i++)
            shots[count++] = i;

        for (int i = n - 1; i >= 2; i--)
            shots[count++] = i;
    }
    else
    {
        for (int i = 2; i <= n - 1; i++)
            shots[count++] = i;

        for (int i = 2; i <= n - 1; i++)
            shots[count++] = i;
    }

    int *possible = calloc(n + 1, sizeof(int));
    int *next = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++)
        possible[i] = 1;

    printf("\nShooting sequence:\n");

    for (int s = 0; s < count; s++)
    {
        int shot = shots[s];

        printf("%d ", shot);


        possible[shot] = 0;

        if (s != count - 1)
        {
            for (int i = 1; i <= n; i++)
                next[i] = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                {
                    if (i > 1)
                        next[i - 1] = 1;

                    if (i < n)
                        next[i + 1] = 1;
                }
            }

            for (int i = 1; i <= n; i++)
                possible[i] = next[i];
        }
    }

    printf("\n\nTarget guaranteed to be hit!\n");
    printf("Number of shots = %d\n", count);

    free(shots);
    free(possible);
    free(next);

    return 0;
}