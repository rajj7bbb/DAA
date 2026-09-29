#include <stdio.h>
#include <limits.h>

unsigned long long collatzNext(unsigned long long n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

void analyzeTrajectory(unsigned long long n)
{
    unsigned long long current = n;
    unsigned long long maxValue = n;
    unsigned long long steps = 0;

    printf("\nTrajectory:\n");

    printf("%llu", current);

    while (current != 1)
    {
        current = collatzNext(current);

        if (current > maxValue)
            maxValue = current;

        printf(" -> %llu", current);

        steps++;
    }

    printf("\n\nStarting value = %llu", n);
    printf("\nNumber of steps = %llu", steps);
    printf("\nMaximum value   = %llu\n", maxValue);
}

void analyzeInterval(unsigned long long a, unsigned long long b)
{
    unsigned long long totalSteps = 0;
    unsigned long long maxValue = 0;
    unsigned long long maxStart = 0;

    printf("\nInterval Analysis [%llu, %llu]\n", a, b);

    for (unsigned long long n = a; n <= b; n++)
    {
        unsigned long long current = n;
        unsigned long long steps = 0;
        unsigned long long localMax = n;

        while (current != 1)
        {
            current = collatzNext(current);

            if (current > localMax)
                localMax = current;

            steps++;
        }

        printf("n = %llu : steps = %llu, max = %llu\n",
               n, steps, localMax);

        totalSteps += steps;

        if (localMax > maxValue)
        {
            maxValue = localMax;
            maxStart = n;
        }

        if (n == b)
            break;
    }

    printf("\nTotal steps = %llu", totalSteps);
    printf("\nLargest trajectory value = %llu", maxValue);
    printf("\nStarting value producing it = %llu\n", maxStart);
}

int main()
{
    unsigned long long n;
    unsigned long long a, b;

    printf("Enter starting value n: ");
    scanf("%llu", &n);

    if (n < 1)
    {
        printf("Invalid input. n must be >= 1.\n");
        return 1;
    }

    analyzeTrajectory(n);

    printf("\nEnter interval [a, b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || a > b)
    {
        printf("Invalid interval.\n");
        return 1;
    }

    analyzeInterval(a, b);

    return 0;
}