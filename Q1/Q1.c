#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Merge Sort
void merge(int arr[], int left, int middle, int right, long long *comparisons) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*comparisons)++; // Counting comparisons
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform Merge Sort
void mergeSort(int arr[], int left, int right, long long *comparisons) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle, comparisons);
        mergeSort(arr, middle + 1, right, comparisons);

        // Merge the sorted halves
        merge(arr, left, middle, right, comparisons);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int option;
    long long comparisons = 0;
    struct timespec start, end;
    FILE *inputFile, *outputFile;

    while (1) {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                inputFile = fopen("inAsce.dat", "r");
                outputFile = fopen("outMergeAsce.dat", "w");
                break;
            case 2:
                inputFile = fopen("inDesc.dat", "r");
                outputFile = fopen("outMergeDesc.dat", "w");
                break;
            case 3:
                inputFile = fopen("inRand.dat", "r");
                outputFile = fopen("outMergeRand.dat", "w");
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option\n");
                continue; // Continue to the next iteration of the loop
        }

        if (inputFile == NULL || outputFile == NULL) {
            printf("Error opening files\n");
            return 1;
        }

        int arr[500]; // Assuming maximum size of 500
        int n = 0;

        while (fscanf(inputFile, "%d", &arr[n]) != EOF) {
            n++;
        }

        fclose(inputFile);

        // Determine the scenario based on the order of input data
        int isAscending = 1;
        int isDescending = 1;

        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[i - 1]) {
                isAscending = 0;
            }
            if (arr[i] > arr[i - 1]) {
                isDescending = 0;
            }
        }

        printf("Before Sorting: ");
        printArray(arr, n);

        // Measure execution time
        clock_gettime(CLOCK_MONOTONIC, &start);
        mergeSort(arr, 0, n - 1, &comparisons);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate execution time in nanoseconds
        long long execution_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

        printf("After Sorting: ");
        printArray(arr, n);

        printf("Number of Comparisons: %lld\n", comparisons);

        // Determine the scenario based on the order of input data
        if (isAscending) {
            printf("Scenario: Best-case (Ascending)\n");
        } else if (isDescending) {
            printf("Scenario: Worst-case (Descending)\n");
        } else {
            printf("Scenario: Average-case (Random)\n");
        }

        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", arr[i]);
        }

        fclose(outputFile);

        printf("Execution Time: %lld nanoseconds\n", execution_time);
    }

    return 0;
}
