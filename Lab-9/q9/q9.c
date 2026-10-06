#include <stdio.h>
#include <limits.h>

#define MAX 100

int w[MAX];
int dp[MAX][MAX];
int root[MAX][MAX];
int prefix[MAX];

int sum(int l, int r) {
    return prefix[r + 1] - prefix[l];
}

int solve(int l, int r) {
    if (l == r)
        return 0;

    if (dp[l][r] != -1)
        return dp[l][r];

    int best = INT_MAX;
    int bestk = -1;

    for (int k = l; k < r; k++) {
        int cost = solve(l, k) +
                   solve(k + 1, r) +
                   sum(l, r);

        if (cost < best) {
            best = cost;
            bestk = k;
        }
    }

    root[l][r] = bestk;
    return dp[l][r] = best;
}

void printTree(int l, int r) {
    if (l == r) {
        printf("%c ", 'A' + l);
        return;
    }

    int k = root[l][r];

    printf("(");
    printTree(l, k);
    printTree(k + 1, r);
    printf(")");
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &w[i]);

    prefix[0] = 0;

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + w[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    int answer = solve(0, n - 1);

    printf("Minimum weighted path length = %d\n", answer);

    printf("Optimal alphabetic tree: ");
    printTree(0, n - 1);
    printf("\n");

    return 0;
}