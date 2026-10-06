#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double v, w, lambda;
} Item;

int cmp(const void *a, const void *b) {
    Item *x = (Item *)a;
    Item *y = (Item *)b;

    if (x->lambda < y->lambda) return 1;
    if (x->lambda > y->lambda) return -1;
    return 0;
}

int main() {
    int n;
    double W;

    scanf("%d %lf", &n, &W);

    Item a[n];

    for (int i = 0; i < n; i++)
        scanf("%lf %lf %lf", &a[i].v, &a[i].w, &a[i].lambda);

    qsort(a, n, sizeof(Item), cmp);

    double remaining = W;
    double time = 0;
    double total = 0;

    for (int i = 0; i < n && remaining > 0; i++) {
        double take = (a[i].w < remaining) ? a[i].w : remaining;

        double density = a[i].v / a[i].w - a[i].lambda * time;

        if (density > 0)
            total += take * density;

        time += take;
        remaining -= take;
    }

    printf("Maximum value = %.2lf\n", total);

    return 0;
}