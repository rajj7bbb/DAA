#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Display(int* a, int length, char* name);
int compare(const void* a, const void* b);
bool findPair(int* S1, int* S2, int n, int x, int* a, int* b);

int main()
{
    int n;
    printf("Enter the number of elements for the sets(n): ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input!\nTry again: ");
        scanf("%d", &n);
    }
    
    int *S1 = (int *)calloc(n, sizeof(int));
    int *S2 = (int *)calloc(n, sizeof(int));

    if (S1 == NULL || S2 == NULL)
    {
        printf("Memory allocation failed!\n");
        free(S1);
        free(S2);
        return 1;
    }

    printf("\nEnter elements for set S1:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", S1 + i);
    }

    printf("\nEnter elements for set S2:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", S2 + i);
    }

    printf("\nEntered sets are: \n");
    Display(S1, n, "S1");
    Display(S2, n, "S2");
    
    int x;
    printf("Enter sum to find(x): ");
    scanf("%d", &x);

    int a = 0, b = 0;
    if (findPair(S1, S2, n, x, &a, &b))
    {
        printf("Found pair: %d + %d = %d\n", a, b, x);
    }
    else
    {
        printf("Pair not found!\n");
    }
    
    free(S1);
    free(S2);
    return 0;
}

void Display(int* a, int length, char* name)
{
    printf("%s: {", name);
    for (int i = 0; i < length; i++)
    {
        printf("%d", a[i]);
        if (i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

// tells qsort how to sort
int compare(const void* a, const void* b)
{
    int x = *(int*)a;
    int y = *(int*)b;
    if (x < y)
    {
        return -1;
    }
    if (x > y)
    {   
        return 1;
    }
    else
    {   
        return 0;
    }
}

bool findPair(int* S1, int* S2, int n, int x, int* a, int* b)
{
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);

    int i = 0, j = n - 1, currentSum = 0;
    while (i < n &&  j >= 0)
    {   
        currentSum = S1[i] + S2[j];
        if (currentSum > x)
        {
            j--;
        }
        else if (currentSum < x)
        {
            i++;
        }
        else
        {
            *a = S1[i];
            *b = S2[j];
            return true;
        }
    }
    return false;
}