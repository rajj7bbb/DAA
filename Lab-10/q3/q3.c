#include <stdio.h>

#define MAX 100005

int parent[MAX], sz[MAX];
long long weight[MAX];

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
    weight[u] += weight[v];
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 1; i <= N; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        unite(u, v);

        long long best = 0;
        int found = 0;

        for (int j = 1; j <= N; j++) {
            if (find(j) == j && sz[j] <= K) {
                if (!found || weight[j] > best) {
                    best = weight[j];
                    found = 1;
                }
            }
        }

        if (found)
            printf("%lld\n", best);
        else
            printf("No eligible component\n");
    }

    return 0;
}