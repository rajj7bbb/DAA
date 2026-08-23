#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Event
{
    int time;
    int type; // +1 for entry, -1 for exit
} Event;

void DisplayEvents(Event* events, int length);
int compare(const void* a, const void* b);

int main()
{
    int n;
    printf("Enter the number of persons attending the party (n): ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input!\nTry again: ");
        scanf("%d", &n);
    }

    // for n person allocate 2n memory so that each person's entry and exit is recorded
    Event* events = (Event*)calloc(2 * n, sizeof(Event));
    if (events == NULL)
    {
        printf("Memory allocation failed!\n");
        free(events);
        return 1;
    }

    printf("\nEnter entry and exit times for each person (ai bi):\n");
    for (int i = 0; i < n; i++)
    {
        int entry, exit;
        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        while (exit <= entry)
        {
            printf("\tExit time must be greater than entry time! Try again: ");
            scanf("%d %d", &entry, &exit);
        }

        // store entering time
        events[2 * i].time = entry;
        events[2 * i].type = 1;

        // store exiting time
        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    printf("\nRecorded %d events:\n", 2 * n);
    DisplayEvents(events, 2 * n);

    // ascending sorting based on time
    qsort(events, 2*n, sizeof(Event), compare);

    int count = 0, maxCount = 0, maxTime = 0;
    for (int i = 0; i < 2*n; i++)
    {   
        count += events[i].type;
        if (count > maxCount)
        {
            maxCount = count;
            maxTime = events[i].time;
        }
    }
    printf("\nMax people %d at time: %d\n", maxCount, maxTime);
    free(events);
    return 0;
}

void DisplayEvents(Event* events, int length)
{
    printf("{");
    for (int i = 0; i < length; i++)
    {
        printf("(%d, %s)", events[i].time, (events[i].type == 1) ? "Entry" : "Exit");
        if (i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

// tells qsort how to sort (ascending based on time here)
int compare(const void* a, const void* b)
{
    Event x = *(Event*)a;
    Event y = *(Event*)b;
    if (x.time < y.time)
    {
        return -1;
    }
    if (x.time > y.time)
    {   
        return 1;
    }
    else
    {   
        return 0;
    }
}