#include <stdio.h>
#include <stdlib.h>

#define MAX 200005

int parent[MAX], sz[MAX];
int p[MAX], ans[MAX];
int indices[MAX], values[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int t = u;
        u = v;
        v = t;
    }

    parent[v] = u;
    sz[u] += sz[v];
}

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x > y) - (x < y);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &p[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    for (int i = 1; i <= N; i++)
        ans[i] = p[i];

    for (int root = 1; root <= N; root++) {
        if (find(root) != root)
            continue;

        int count = 0;

        for (int i = 1; i <= N; i++) {
            if (find(i) == root) {
                indices[count] = i;
                values[count] = p[i];
                count++;
            }
        }

        qsort(indices, count, sizeof(int), cmp);
        qsort(values, count, sizeof(int), cmp);

        for (int i = 0; i < count; i++)
            ans[indices[i]] = values[i];
    }

    for (int i = 1; i <= N; i++)
        printf("%d ", ans[i]);

    printf("\n");

    return 0;
}