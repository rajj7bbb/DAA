#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int state;
    int moves;
} Node;

int isLegal(int state, int i)
{
    // Rightmost switch can always be toggled
    if (i == 0)
        return 1;

    /*
       For switch i:
       bit i-1 must be 1
       all bits to its right must be 0
    */

    int rightPart = state & ((1 << i) - 1);

    return rightPart == (1 << (i - 1));
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n >= 30)
    {
        printf("Enter n between 1 and 29.\n");
        return 1;
    }

    int totalStates = 1 << n;

    int start = totalStates - 1;
    int goal = 0;

    int *visited = calloc(totalStates, sizeof(int));
    int *parent = malloc(totalStates * sizeof(int));
    int *moveUsed = malloc(totalStates * sizeof(int));
    int *distance = malloc(totalStates * sizeof(int));

    int *queue = malloc(totalStates * sizeof(int));

    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    visited[start] = 1;
    parent[start] = -1;
    distance[start] = 0;

    while (front < rear)
    {
        int state = queue[front++];

        if (state == goal)
            break;

        for (int i = 0; i < n; i++)
        {
            if (isLegal(state, i))
            {
                int newState = state ^ (1 << i);

                if (!visited[newState])
                {
                    visited[newState] = 1;
                    parent[newState] = state;
                    moveUsed[newState] = i;
                    distance[newState] = distance[state] + 1;

                    queue[rear++] = newState;
                }
            }
        }
    }

    printf("\nMinimum number of moves = %d\n",
           distance[goal]);

    /* Reconstruct the solution */
    int *path = malloc((distance[goal] + 1) * sizeof(int));

    int current = goal;
    int count = 0;

    while (current != start)
    {
        path[count++] = moveUsed[current];
        current = parent[current];
    }

    printf("\nSwitches toggled (from right):\n");

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%d ", path[i] + 1);
    }

    printf("\n");

    free(visited);
    free(parent);
    free(moveUsed);
    free(distance);
    free(queue);
    free(path);

    return 0;
}