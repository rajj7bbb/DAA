#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Structure to store search performance statistics */
typedef struct {
    int index;              /* Found index (-1 if element is absent) */
    long long comparisons;  /* Total element comparison operations */
    int iterations;         /* Total loop iterations */
} SearchResult;

//-----------------------
// Standard Binary Search
//-----------------------

void binarySearch(const int arr[], int n, int target, SearchResult *result) {
    int low = 0;
    int high = n - 1;
    result->comparisons = 0;
    result->iterations = 0;
    result->index = -1;

    while (low <= high) {
        result->iterations++;
        int mid = low + (high - low) / 2;

        /* Comparison 1: Check equality */
        result->comparisons++;
        if (arr[mid] == target) {
            result->index = mid;
            return;
        }

        /* Comparison 2: Determine branch */
        result->comparisons++;
        if (arr[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
}

//------------------------
// Standard Ternary Search
//------------------------

void ternarySearch(const int arr[], int n, int target, SearchResult *result) {
    int low = 0;
    int high = n - 1;
    result->comparisons = 0;
    result->iterations = 0;
    result->index = -1;

    while (low <= high) {
        result->iterations++;
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        /* Comparison 1: Check mid1 equality */
        result->comparisons++;
        if (arr[mid1] == target) {
            result->index = mid1;
            return;
        }

        /* Comparison 2: Check mid2 equality */
        result->comparisons++;
        if (arr[mid2] == target) {
            result->index = mid2;
            return;
        }

        /* Comparison 3: Check left partition */
        result->comparisons++;
        if (target < arr[mid1]) {
            high = mid1 - 1;
        } 
        /* Comparison 4: Check right partition */
        else {
            result->comparisons++;
            if (target > arr[mid2]) {
                low = mid2 + 1;
            } else {
                /* Target is in the middle partition */
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
}

/**
 * Helper to display elements of an array
 */
void printArray(const int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

/**
 * Print mathematical justification comparing Binary vs. Ternary search
 */
void printTheoreticalJustification(void) {
    printf("\n========================================================================================\n");
    printf("                     THEORETICAL & MATHEMATICAL JUSTIFICATION                           \n");
    printf("========================================================================================\n");
    printf("1. RECURRENCE RELATIONS & TREE HEIGHT:\n");
    printf("   - Binary Search  : T(n) = T(n / 2) + 2   => Height = log2(n)\n");
    printf("   - Ternary Search : T(n) = T(n / 3) + 4   => Height = log3(n)\n\n");

    printf("2. WORST-CASE COMPARISON COMPLEXITY:\n");
    printf("   - Binary Search  : C_binary(n)  = 2 * log2(n) = 2 * (ln(n) / ln(2))   ≈ 2.885 * ln(n)\n");
    printf("   - Ternary Search : C_ternary(n) = 4 * log3(n) = 4 * (ln(n) / ln(3))   ≈ 3.641 * ln(n)\n\n");

    printf("3. COMPARISON RATIO:\n");
    printf("   C_ternary(n) / C_binary(n) = (4 / log2(3)) / 2 = 2 / 1.58496 ≈ 1.2618 (26.2%% MORE comparisons)\n\n");

    printf("CONCLUSION:\n");
    printf("   Although Ternary Search reduces the tree height from log2(n) to log3(n),\n");
    printf("   the increased number of comparisons per level (up to 4 vs 2) outweighs the\n");
    printf("   depth reduction. Thus, BINARY SEARCH IS PROVEN TO BE MORE EFFICIENT.\n");
    printf("========================================================================================\n");
}

/**
 * Interactive search mode for custom user inputs
 */
void runInteractiveMode(void) {
    int n;
    printf("\n--- Interactive Search Mode ---\n");
    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid array size.\n");
        return;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    printf("Enter %d sorted integers in ascending order:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Error: Invalid integer input.\n");
            free(arr);
            return;
        }
    }

    /* Validate sorted property */
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("\n[Warning] Input array is NOT sorted!\n");
            break;
        }
    }

    int target;
    printf("Enter element x to search: ");
    if (scanf("%d", &target) != 1) {
        printf("Error: Invalid target input.\n");
        free(arr);
        return;
    }

    printf("\nGiven Array: ");
    printArray(arr, n);
    printf("Search Target: %d\n\n", target);

    SearchResult bsRes, tsRes;
    binarySearch(arr, n, target, &bsRes);
    ternarySearch(arr, n, target, &tsRes);

    printf("=====================================================\n");
    printf("                 SEARCH EXECUTION RESULTS            \n");
    printf("=====================================================\n");
    printf(" 1. BINARY SEARCH:\n");
    if (bsRes.index != -1) {
        printf("    * Status            : FOUND at index %d\n", bsRes.index);
    } else {
        printf("    * Status            : NOT FOUND\n");
    }
    printf("    * Loop Iterations   : %d\n", bsRes.iterations);
    printf("    * Total Comparisons : %lld\n", bsRes.comparisons);
    printf("-----------------------------------------------------\n");

    printf(" 2. TERNARY SEARCH:\n");
    if (tsRes.index != -1) {
        printf("    * Status            : FOUND at index %d\n", tsRes.index);
    } else {
        printf("    * Status            : NOT FOUND\n");
    }
    printf("    * Loop Iterations   : %d\n", tsRes.iterations);
    printf("    * Total Comparisons : %lld\n", tsRes.comparisons);
    printf("=====================================================\n");

    printf("\nComparison Summary:\n");
    if (bsRes.comparisons < tsRes.comparisons) {
        long long diff = tsRes.comparisons - bsRes.comparisons;
        double pct = ((double)diff / tsRes.comparisons) * 100.0;
        printf(">> Binary Search was MORE efficient by %lld comparison(s) (%.1f%% fewer comparisons).\n", diff, pct);
    } else if (bsRes.comparisons == tsRes.comparisons) {
        printf(">> Both algorithms performed identical number of comparisons (%lld).\n", bsRes.comparisons);
    } else {
        printf(">> Ternary Search performed fewer comparisons for this target position.\n");
    }

    free(arr);
}

int main(void) {
    int choice;
    while (1) {
        printf("\n========================================================\n");
        printf("          BINARY SEARCH VS TERNARY SEARCH LAB           \n");
        printf("========================================================\n");
        printf("  1. Interactive Search (Input your array & target x)   \n");
        printf("  2. View Mathematical & Theoretical Justification      \n");
        printf("  3. Exit                                               \n");
        printf("========================================================\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 1:
                runInteractiveMode();
                break;
            case 2:
                printTheoreticalJustification();
                break;
            case 3:
                printf("\nExiting program. Thank you!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }
    return 0;
}
