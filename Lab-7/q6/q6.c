#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    int birth[n];
    int death[n];

    printf("Enter birth and death years:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &birth[i], &death[i]);
    }

    qsort(birth, n, sizeof(int), compare);

    qsort(death, n, sizeof(int), compare);

    int i = 0;
    int j = 0;

    int alive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    while (i < n)
    {

        if (birth[i] < death[j])
        {
            alive++;

            if (alive > maxAlive)
            {
                maxAlive = alive;
                bestYear = birth[i];
            }

            i++;
        }
        else
        {
            alive--;
            j++;
        }
    }

    printf("\nMaximum number of scientists alive = %d\n",
           maxAlive);

    printf("A time when this maximum occurs = %d\n",
           bestYear);

    return 0;
}