#include <stdio.h>
#include <stdlib.h>

typedef struct Interval
{
    int start;
    int end; 
} Interval; 

int compare(const void* a, const void* b);
void DisplayInterval(const Interval* interval, int n);

int main(){
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid Input! Try again: ");
        scanf("%d", &n);
    }

    Interval *I = (Interval*)calloc(n, sizeof(Interval));
    if (I == NULL)
    {
        printf("Memory allocation failed!\n");
        free(I);
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter interval %d start and end time: ", i + 1);
        scanf("%d %d", &I[i].start, &I[i].end);
        while (I[i].start >= I[i].end)
        {
            printf("Invalid Input! Try again: ");
            scanf("%d %d", &I[i].start, &I[i].end);
        }
    }
    DisplayInterval(I, n);
    qsort(I, n, sizeof(Interval), compare);
    
    Interval *result = (Interval *)calloc(n, sizeof(Interval));
    if (result == NULL)
    {
        printf("Memory allocation failed!\n");
        free(I);
        free(result);
        return 1;
    }
    
    int k = 0;

    Interval current = I[0];
    for (int i = 1; i < n; i++)
    {
        if (I[i].start <= current.end)
        {
            if (current.end < I[i].end)
            {
                current.end = I[i].end;
            }
        }
        else
        {
            result[k++] = current;
            current = I[i];
        }
    }
    result[k++] = current;
    
    DisplayInterval(result, k);
    
    free(I);
    free(result);
    return 0;
}

int compare(const void* a, const void* b)
{
    Interval x = *(Interval*)a;
    Interval y = *(Interval*)b;

    if (x.start > y.start)
    {
        return 1;
    }
    else if (x.start < y.start)
    {
        return -1;
    }
    return 0;
}

void DisplayInterval(const Interval* interval, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("(%d, %d)", interval[i].start, interval[i].end);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
    
}