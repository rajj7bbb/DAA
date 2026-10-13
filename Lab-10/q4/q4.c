#include <stdio.h>

#define MAX 200005

int parent[MAX], sz[MAX];
int active[MAX];
int U[MAX], V[MAX], order[MAX];
int head[MAX], to[2 * MAX], next[2 * MAX], ec;
long long weight[MAX], sum[MAX], ans[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void addEdge(int u, int v) {
    to[ec] = v;
    next[ec] = head[u];
    head[u] = ec++;
}

long long unite(int u, int v, long long best) {
    u = find(u);
    v = find(v);

    if (u == v)
        return best;

    if (sz[u] < sz[v]) {
        int t = u;
        u = v;
        v = t;
    }

    parent[v] = u;
    sz[u] += sz[v];
    sum[u] += sum[v];

    if (sum[u] > best)
        best = sum[u];

    return best;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
        head[i] = -1;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &U[i], &V[i]);

        addEdge(U[i], V[i]);
        addEdge(V[i], U[i]);
    }

    for (int i = 0; i < N; i++)
        scanf("%d", &order[i]);

    long long best = 0;

    for (int i = N - 1; i >= 0; i--) {
        int u = order[i];

        active[u] = 1;
        sum[u] = weight[u];

        if (sum[u] > best)
            best = sum[u];

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (active[v])
                best = unite(u, v, best);
        }

        ans[i] = best;
    }

    for (int i = 0; i < N; i++)
        printf("%lld\n", ans[i]);

    return 0;
}