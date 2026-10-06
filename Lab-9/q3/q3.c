#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int d;
    int fuel;
} Station;

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

        if (heap[p] >= heap[i])
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
        int largest = i;

        if (l < *n && heap[l] > heap[largest])
            largest = l;

        if (r < *n && heap[r] > heap[largest])
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return ans;
}

int cmp(const void *a, const void *b) {
    Station *x = (Station *)a;
    Station *y = (Station *)b;
    return x->d - y->d;
}

int main() {
    int D, F, n;

    scanf("%d %d %d", &D, &F, &n);

    Station s[n];

    for (int i = 0; i < n; i++)
        scanf("%d %d", &s[i].d, &s[i].fuel);

    qsort(s, n, sizeof(Station), cmp);

    int heap[n];
    int hsize = 0;
    int stops = 0;
    int i = 0;
    int position = 0;

    while (position + F < D) {

        while (i < n && s[i].d <= position + F) {
            push(heap, &hsize, s[i].fuel);
            i++;
        }

        if (hsize == 0) {
            printf("-1\n");
            return 0;
        }

        int extra = pop(heap, &hsize);
        F += extra;
        stops++;
    }

    printf("Minimum stops = %d\n", stops);

    return 0;
}