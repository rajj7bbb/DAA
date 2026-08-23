#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void Display(int* a, int length, char* name);
int compare(const void* a, const void* b);
bool kElementsExist(int* S, int n, int l, int T, int k);
int binarySearch(int *S, int l, int u, int target);

int main()
{
    int n;
    printf("Enter the number of elements for the set(n): ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input!\nTry again: ");
        scanf("%d", &n);
    }
    
    int *S = (int *)calloc(n, sizeof(int));

    if (S == NULL)
    {
        printf("Memory allocation failed!\n");
        free(S);
        return 1;
    }

    printf("\nEnter elements for set S:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", S + i);
    }

    printf("\nEntered set is: \n");
    Display(S, n, "S");
    
    int T;
    printf("Enter sum to find(T): ");
    scanf("%d", &T);

    int k;
    printf("Enter number of integers(k) to add up to sum: ");
    scanf("%d", &k);
    while (k <= 0 || k > n)
    {
        printf("\nInvalid input!\nTry again: ");
        scanf("%d", &k);
    }
    
    qsort(S, n, sizeof(int), compare);
    // Display(S, n, "S");

    printf("\nResult: ");
    if (kElementsExist(S, n, 0, T, k))
    {
        printf(" \t= %d \nFound!\n", T);
    }
    else
    {
        printf("Not found!\n");
    }

    free(S);
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

// qsort(S1, n, sizeof(int), compare);

int binarySearch(int *S, int l, int u, int target)
{
    int mid;
    while(l <= u)
    {
        mid = l + (u - l)/2;
        if (S[mid] == target)
        {
            return mid;
        }
        else if (S[mid] > target)
        {
            u = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
    
}

bool kElementsExist(int* S, int n, int l, int T, int k)
{
    if (k == 1)
    {
        int index = binarySearch(S, l, n - 1, T);
        if(index >= 0)
        {
            printf("  %d\n", S[index]);
            return true;
        }
        return false;
    }
    
    for (int i = l; i <= n - k; i++)
    {
        if (kElementsExist(S, n, i + 1, T - S[i], k - 1))
        {
            printf(" \t+ %d\n", S[i]);
            return true;
        }
    }
    return false;
}