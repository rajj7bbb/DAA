#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Event
{
    int point; // coordinate on the line
    int type;  // +1 for start (left endpoint), -1 for end (right endpoint)
} Event;

void DisplayEvents(Event* events, int length);
int compare(const void* a, const void* b);

int main()
{
    int n;
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input!\nTry again: ");
        scanf("%d", &n);
    }

    // For n intervals, allocate 2n memory so each interval's start and end is recorded
    Event* events = (Event*)calloc(2 * n, sizeof(Event));
    if (events == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nEnter left and right endpoints for each interval (li ri):\n");
    for (int i = 0; i < n; i++)
    {
        int left, right;
        printf("Interval %d: ", i + 1);
        scanf("%d %d", &left, &right);

        while (left > right)
        {
            printf("\tLeft endpoint must be <= right endpoint! Try again: ");
            scanf("%d %d", &left, &right);
        }

        // Store start endpoint
        events[2 * i].point = left;
        events[2 * i].type = 1;

        // Store end endpoint
        events[2 * i + 1].point = right;
        events[2 * i + 1].type = -1;
    }

    printf("\nRecorded %d events:\n", 2 * n);
    DisplayEvents(events, 2 * n);
    
    qsort(events, 2 * n, sizeof(Event), compare);

    printf("\nSorted events:\n");
    DisplayEvents(events, 2 * n);

    int p = 0;        // the point in maximum intervals
    int count = 0;
    int maxCount = 0; // maximum number of overlapping intervals

    for (int i = 0; i < 2 * n; i++)
    {       
        count += events[i].type;
        if (count > maxCount)
        {
            maxCount = count;
            p = events[i].point;
        }
        
    }
    

    printf("\nPoint in maximum intervals: p = %d (overlaps with %d intervals)\n", p, maxCount);

    free(events);
    return 0;
}

void DisplayEvents(Event* events, int length)
{
    printf("{");
    for (int i = 0; i < length; i++)
    {
        printf("(%d, %s)", events[i].point, (events[i].type == 1) ? "Start" : "End");
        if (i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

int compare(const void* a, const void* b)
{
    Event x = *(Event*)a;
    Event y = *(Event*)b;

    if (x.point != y.point) // if diff points then rank by points
    {
        return (x.point > y.point) ? 1 : -1;
    }
    if (x.type != y.type) // if same point then start comes first
    {
        return (x.type == 1) ? -1 : 1;
    }
    return 0;

    /*
    +ve a comes after b
    -ve a comes before b
    0 a == b
    */
    
}