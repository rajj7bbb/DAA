#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

long long bubble_sort_optimized(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return comparisons;
}

long long bubble_sort_standard(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

int main() {
    srand((unsigned int)time(NULL));

    FILE *dataFile = fopen("bubble_data.txt", "w");
    if (dataFile == NULL) {
        perror("Error opening bubble_data.txt");
        return 1;
    }

    fprintf(dataFile, "# N Optimized Standard Theoretical\n");

    int min_size = 10;
    int max_size = 200;
    int step = 10;

    for (int n = min_size; n <= max_size; n += step) {
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        // Generate randomized data sequence
        for (int i = 0; i < n; i++) {
            int val = rand() % 10000;
            arr1[i] = val;
            arr2[i] = val; // Duplicate for identical benchmark condition
        }

        long long comps_opt = bubble_sort_optimized(arr1, n);
        long long comps_std = bubble_sort_standard(arr2, n);
        long long theoretical = (long long)n * (n - 1) / 2;

        fprintf(dataFile, "%d %lld %lld %lld\n", n, comps_opt, comps_std, theoretical);

        free(arr1);
        free(arr2);
    }
    fclose(dataFile);
    printf("Data written to 'bubble_data.txt'. Sending plot commands to Gnuplot...\n");

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Gnuplot pipe error. Ensure gnuplot is installed and in system PATH.");
        return 1;
    }

    fprintf(gnuplotPipe, "set title 'Bubble Sort Efficiency: Optimized vs Standard (Random Data)'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size (n)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Number of Comparisons'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set key top left\n");
    fprintf(gnuplotPipe, "plot 'bubble_data.txt' using 1:3 with linespoints lw 2 title 'Standard (n-1 passes)', \\\n");
    fprintf(gnuplotPipe, "     'bubble_data.txt' using 1:2 with linespoints lw 2 title 'Optimized (Early Termination)'\n");

    pclose(gnuplotPipe);
    return 0;
}