#include <stddef.h>
#include <stdlib.h>
#include <common.h>

size_t g_quick_cmp_count = 0;

/**
 * Partitions the array, pivot is "rightmost" element
 * @param arr : the array to pivot
 * @param start : starting index to partition
 * @param end : end index to partition
 * @return index of the pivot after partitioning
 */
static
int
partition (int arr[], int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            ++i; // increment index of smaller element
            COMMON__swap_int(&arr[i], &arr[j]);
        }
        ++g_quick_cmp_count;
    }

    COMMON__swap_int(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/**
 * Implement the randomized-partition algorithm.
 * @param arr : the array to partition
 * @param start : starting index for the partitioning
 * @param end : end index for the partitioning
 * @return index of the pivot after partitioning
 */
static
size_t
randomized_partition(int arr[], size_t start, size_t end) {
    size_t random_index = 0;

    random_index = (rand() % (end - start + 1)) + start;
    COMMON__swap_int(&arr[end], &arr[random_index]);

    return partition(arr, (int)start, (int)end);
}

/**
 * Implements the randomized-select algorithm
 * @param arr the array from which we look for the k-th smallest element
 * @param start first index of the array
 * @param end last index of the array
 * @param k which k-th element to look for
 * @return
 */
int
QUICK__randomized_select(int arr[], size_t start, size_t end, size_t k) {
    size_t pivot_index = 0;
    size_t low_partition_size = 0;

    if(start == end) {
        return arr[start];
    }

    pivot_index = randomized_partition(arr, start, end);
    low_partition_size = pivot_index - start + 1;

    // pivot is the k-th lowest element
    if (k == low_partition_size) {
        return arr[pivot_index];
    }
    // the k-th lowest element is in the low partition
    else if (k < low_partition_size) {
        return QUICK__randomized_select(arr, start, pivot_index - 1, k);
    }
    // the k-th lowest element is in the high partition
    else {
        return QUICK__randomized_select(arr, pivot_index + 1, end, k - low_partition_size);
    }
}

/**
 * Implements the quicksort algorithm
 * @param arr : the array we will be sorting
 * @param low : first index of arr
 * @param high : last index of arr
 */
void
QUICK__quicksort(int arr[], int low, int high)
    {
        if (low < high) {
            int partition_index = partition(arr, low, high);

            // sort both sides of the partition
            QUICK__quicksort(arr, low, partition_index - 1);
            QUICK__quicksort(arr, partition_index + 1, high);
        }
    }
