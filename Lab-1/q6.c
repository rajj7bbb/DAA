#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int has_duplicate_pairwise(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return 1;   
            }
        }
    }
    return 0;  
}

int compare_ints(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

int has_duplicate_after_sort(int arr[], int size) {

    int *sorted_copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        sorted_copy[i] = arr[i];
    }

    qsort(sorted_copy, size, sizeof(int), compare_ints);

    int found_duplicate = 0;
    for (int i = 0; i < size - 1; i++) {
        if (sorted_copy[i] == sorted_copy[i + 1]) {
            found_duplicate = 1;
            break;
        }
    }

    free(sorted_copy);
    return found_duplicate;
}

void fill_with_random_numbers(int arr[], int size, int range) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % range;
    }
}

int main(void) {
    srand((unsigned) time(NULL));

    printf("=== Quick correctness check ===\n");
    int no_dup_example[]  = {5, 3, 8, 1, 9, 2};
    int has_dup_example[] = {5, 3, 8, 1, 9, 3};   

    printf("Array with no duplicates -> pairwise says: %d, sort-based says: %d\n",
           has_duplicate_pairwise(no_dup_example, 6), has_duplicate_after_sort(no_dup_example, 6));
    printf("Array WITH a duplicate   -> pairwise says: %d, sort-based says: %d\n\n",
           has_duplicate_pairwise(has_dup_example, 6), has_duplicate_after_sort(has_dup_example, 6));

    printf("=== Timing comparison: pairwise (n^2) vs sort-based (n log n) ===\n");
    int sizes_to_test[] = {2000, 4000, 8000, 16000, 32000};
    int num_tests = sizeof(sizes_to_test) / sizeof(sizes_to_test[0]);

    printf("%-8s %-18s %-18s\n", "n", "pairwise (sec)", "sort-based (sec)");

    for (int t = 0; t < num_tests; t++) {
        int size = sizes_to_test[t];
        int *arr = malloc(size * sizeof(int));
        fill_with_random_numbers(arr, size, 1000000000);

        clock_t start_time = clock();
        int result_pairwise = has_duplicate_pairwise(arr, size);
        clock_t after_pairwise = clock();
        int result_sorted = has_duplicate_after_sort(arr, size);
        clock_t after_sorted = clock();

        double pairwise_seconds = (double)(after_pairwise - start_time) / CLOCKS_PER_SEC;
        double sorted_seconds   = (double)(after_sorted - after_pairwise) / CLOCKS_PER_SEC;

       
        printf("%-8d %-18.5f %-18.5f  (duplicate found: pairwise=%d, sorted=%d)\n",
               size, pairwise_seconds, sorted_seconds, result_pairwise, result_sorted);

        free(arr);
    }

    printf("\nWhat to notice:\n");
    printf(" - The pairwise method's time grows roughly n^2: doubling n makes\n");
    printf("   it take about 4 times as long.\n");
    printf(" - The sort-based method's time grows much more gently (n log n),\n");
    printf("   so it pulls further and further ahead as n gets bigger.\n");
    printf(" - (A hash-set based approach could do this in Theta(n) time on\n");
    printf("   average, using extra memory -- worth exploring as a bonus!)\n");

    return 0;
}