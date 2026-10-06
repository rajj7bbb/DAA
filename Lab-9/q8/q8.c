#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Meeting;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void push(int heap[], int *n, int x) {
    int i = (*n)++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (heap[p] <= heap[i])
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

int pop(int heap[], int *n) {
    int ans = heap[0];

    heap[0] = heap[--(*n)];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < *n && heap[l] < heap[smallest])
            smallest = l;

        if (r < *n && heap[r] < heap[smallest])
            smallest = r;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return ans;
}

int cmp(const void *a, const void *b) {
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;

    return x->start - y->start;
}

int main() {
    int n;
    scanf("%d", &n);

    Meeting m[n];

    for (int i = 0; i < n; i++)
        scanf("%d %d", &m[i].start, &m[i].end);

    qsort(m, n, sizeof(Meeting), cmp);

    int heap[n];
    int size = 0;
    int rooms = 0;

    for (int i = 0; i < n; i++) {

        while (size > 0 && heap[0] <= m[i].start)
            pop(heap, &size);

        push(heap, &size, m[i].end);

        if (size > rooms)
            rooms = size;
    }

    printf("Minimum number of rooms = %d\n", rooms);

    return 0;
}