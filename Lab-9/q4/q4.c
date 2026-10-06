#include <stdio.h>

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

int main() {
    int n;
    scanf("%d", &n);

    int heap[n];
    int size = 0;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        push(heap, &size, x);
    }

    int cost = 0;

    while (size > 1) {
        int x = pop(heap, &size);
        int y = pop(heap, &size);

        int sum = x + y;

        cost += sum;
        push(heap, &size, sum);
    }

    printf("Minimum cost = %d\n", cost);

    return 0;
}