#include <stdio.h>

#define MAX 1000005

int parent[MAX], sz[MAX], active[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];

    return 1;
}

int main() {
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);

    int N = R * C;

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        sz[i] = 1;
        active[i] = 0;
    }

    int islands = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < K; i++) {
        int r, c;
        scanf("%d %d", &r, &c);

        r--;
        c--;

        int id = r * C + c;

        if (!active[id]) {
            active[id] = 1;
            islands++;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= R ||
                    nc < 0 || nc >= C)
                    continue;

                int nid = nr * C + nc;

                if (active[nid] && unite(id, nid))
                    islands--;
            }
        }

        printf("%d\n", islands);
    }

    return 0;
}