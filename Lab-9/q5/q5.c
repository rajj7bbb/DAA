#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int rating[n];
    int left[n], right[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &rating[i]);

    for (int i = 0; i < n; i++)
        left[i] = 1;

    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            left[i] = left[i - 1] + 1;
    }

    for (int i = 0; i < n; i++)
        right[i] = 1;

    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1])
            right[i] = right[i + 1] + 1;
    }

    int total = 0;

    for (int i = 0; i < n; i++) {
        int candy = left[i] > right[i] ? left[i] : right[i];
        total += candy;
    }

    printf("Minimum candies = %d\n", total);

    return 0;
}