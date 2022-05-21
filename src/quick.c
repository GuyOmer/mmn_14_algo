#include <stddef.h>
#include <stdlib.h>
#include <common.h>
#include <retvals.h>

size_t g_quick_cmp_count = 0;

/**
 * Partitions the array, pivot is "rightmost" element
 * @param arr : the array to pivot
 * @param start : starting index to partition
 * @param end : end index to partition
 * @return index of the pivot after partitioning
 */
static
size_t
partition(int arr[], size_t start, size_t end) {
    int pivot = arr[end];
    int i = (int)start  - 1;

    for (int j = start; j <= end; ++j) {
        ++g_quick_cmp_count;
        if (arr[j] <= pivot) {
            ++i;
            COMMON__swap_int(&arr[i], &arr[j]);
        }
    }
    COMMON__swap_int(&arr[i+1], &arr[end]);

    return i+1;
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

    return partition(arr, start, end);
}

int
QUICK__randomized_select(int arr[], size_t start, size_t end, size_t k) {
    size_t pivot_index = 0;
    size_t low_partition_size = 0;

    if(start == end) {
        return arr[start];
    }

    pivot_index = randomized_partition(arr, start, end - 1);
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

retval_t
QUICK__quicktsort(int arr[], size_t start, size_t end) {
    retval_t retval = UNINITIALIZED;
    int pivot_index = 0;

    if(arr == NULL) {
        retval = INVALID_PARAMETERS;
        goto l_cleanup;
    }
    if (start < end) {
        pivot_index = partition(arr, start, end);
        (void)QUICK__quicktsort(arr, start, pivot_index - 1);
        (void)QUICK__quicktsort(arr, pivot_index + 1, end);
    }

    retval = SUCCESS;

l_cleanup:
    return retval;
}
