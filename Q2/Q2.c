#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Quick Sort
int partition(int arr[], int low, int high, long long *comparisons) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        (*comparisons)++; // Counting comparisons
    }


    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Function to perform Quick Sort
void quickSort(int arr[], int low, int high, long long *comparisons) {
    if (low < high) {

        int pi = partition(arr, low, high, comparisons);


        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
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
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                inputFile = fopen("inAsce.dat", "r");
                outputFile = fopen("outQuickAsce.dat", "w");
                break;
            case 2:
                inputFile = fopen("inDesc.dat", "r");
                outputFile = fopen("outQuickDesc.dat", "w");
                break;
            case 3:
                inputFile = fopen("inRand.dat", "r");
                outputFile = fopen("outQuickRand.dat", "w");
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

        printf("Before Sorting: ");
        printArray(arr, n);

        // Measure execution time
        clock_gettime(CLOCK_MONOTONIC, &start);
        quickSort(arr, 0, n - 1, &comparisons);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate execution time in nanoseconds
        long long execution_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

        printf("After Sorting: ");
        printArray(arr, n);

        printf("Number of Comparisons: %lld\n", comparisons);

        // Determine the scenario based on the number of comparisons
        if (comparisons == n - 1) {
            printf("Scenario: Worst-case\n");
        } else if (comparisons <= (long long)(n * (n - 1)) / 2) {
            printf("Scenario: Best-case\n");
        } else {
            printf("Scenario: Average-case\n");
        }

        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", arr[i]);
        }

        fclose(outputFile);

        printf("Execution Time: %lld nanoseconds\n", execution_time);
    }

    return 0;
}
