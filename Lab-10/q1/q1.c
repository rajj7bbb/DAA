#include <stdio.h>

#define MAX 100005

int parent[MAX], sz[MAX], parity[MAX];

int find(int x) {
    if (parent[x] == x)
        return x;

    int p = parent[x];
    parent[x] = find(p);
    parity[x] ^= parity[p];

    return parent[x];
}

int unite(int u, int v) {
    int ru = find(u);
    int pu = parity[u];

    int rv = find(v);
    int pv = parity[v];

    if (ru == rv)
        return (pu ^ pv) == 1;

    if (sz[ru] < sz[rv]) {
        int t = ru;
        ru = rv;
        rv = t;
    }

    parent[rv] = ru;
    parity[rv] = pu ^ pv ^ 1;
    sz[ru] += sz[rv];

    return 1;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        sz[i] = 1;
        parity[i] = 0;
    }

    int bipartite = 1;

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (bipartite && !unite(u, v))
            bipartite = 0;

        printf("%s\n", bipartite ? "Bipartite" : "Not Bipartite");
    }

    return 0;
}