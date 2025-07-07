#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Function to sort array using insertion sort */
void insertionSort(int arr[], int n)
{
    for (int i = 2; i <= n; ++i) {
        // Sentinel
        int key = arr[i];
        arr[0] = key;  // Set sentinel value

        int j = i - 1;

        while (arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i = 1; i <= n; ++i) // Start from index 1
        printf("%d ", arr[i]);
    printf("\n");
}

int* createArray(int n) {
    // Dynamically allocate array with n+1 elements (index 0 for sentinel)
    int* arr = (int*)malloc((n + 1) * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 1; i <= n; ++i) {
        arr[i] = n - i; // Example: Fill array in descending order
    }

    return arr;
}

// Driver method
int main()
{
    int n;
    printf("Number of elements desired: \n");
    scanf("%d", &n);

    // Create array
    int* arr = createArray(n);

    // Print array
    printArray(arr, n);

    // Sort array
    insertionSort(arr, n);

    // Print sorted array
    printArray(arr, n);

    // Free allocated memory
    free(arr);

    return 0;
}
