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

int main() {
    int n;
    scanf("%d", &n);

    int heap[n];
    int size = 0;
    int minVal = 1000000000;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        if (x % 2 != 0)
            x *= 2;

        if (x < minVal)
            minVal = x;

        push(heap, &size, x);
    }

    int ans = heap[0] - minVal;

    while (1) {
        int maxVal = pop(heap, &size);

        if (maxVal - minVal < ans)
            ans = maxVal - minVal;

        if (maxVal % 2 != 0)
            break;

        maxVal /= 2;

        if (maxVal < minVal)
            minVal = maxVal;

        push(heap, &size, maxVal);
    }

    printf("Minimum deviation = %d\n", ans);

    return 0;
}