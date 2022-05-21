#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "retvals.h"
#include "common.h"
#include "heap.h"
#include "quick.h"
#include "input.h"

#define RANGE_MIN (0)
#define RANGE_MAX (999)

/**
 * Initializes the array with values according to user input.
 *
 * @param amount_of_values: The amount of the values in the array
 * @param arr: The array to initialize
 * @retval: SUCCESS if successful, otherwise an appropriate status code
 */
static
retval_t
initialize_array(size_t amount_of_values, int **arr) {
    retval_t retval = UNINITIALIZED;
    int *internal_arr = NULL;
    bool should_randomize_arr = false;
    char should_randomize_input_user_input = '\0';
    int number_user_input = 0;

    if(arr == NULL) {
        retval = INVALID_PARAMETERS;
        goto l_cleanup;
    }

    internal_arr = (int *)malloc(sizeof(*arr) * amount_of_values);
    if (arr == NULL) {
        retval = MAIN__FAILED_ALLOCATION_ARRAY;
        goto l_cleanup;
    }

    // keep asking for input until an appropriate input
    while (1) {
//        should_randomize_input_user_input = get_char("Should randomize characters (y\\n): ");
        should_randomize_input_user_input = 'y';
        if (should_randomize_input_user_input == 'y') {
            should_randomize_arr = true;
            break;
        }
        else if (should_randomize_input_user_input == 'n') {
            should_randomize_arr = false;
            break;
        }
    }

    if (should_randomize_arr) {
        for (size_t i = 0; i < amount_of_values; ++i) {
            internal_arr[i] = rand() % (RANGE_MAX + 1); // [RANGE_MIN ... RANGE_MAX]
        }
    }
    else {
        for (size_t i = 0; i < amount_of_values; ++i) {
            number_user_input = get_int("Enter value for element at %zu: ", i);
            if(number_user_input > 999) {
                (void)printf("Number must be between %d and %d\n", RANGE_MIN, RANGE_MAX);
                --i;
                continue;
            }
            internal_arr[i] = number_user_input;
        }
    }


    // transfer of ownership
    *arr = internal_arr;
    internal_arr = NULL;

    retval = SUCCESS;

l_cleanup:
    if (internal_arr != NULL) {
        free(internal_arr);
    }

    return  retval;
}

/**
 * Run the quicksort based method.
 * Will first use the 'randomized-select' algorithm the find the k-th smallest item.
 * Then, sort k elements with 'quicksort'.
 * @param k: k-th smallest item in the array we will be finding and sorting uo to
 * @param length: length of the array
 * @param arr: The array to operate on
 * @return: SUCCESS if successful, otherwise an appropriate status code
 */
static
retval_t
run_quick(size_t k, size_t length, int *arr) {
    retval_t retval = UNINITIALIZED;
    int k_smallest_value = 0;
    size_t k_smallest_value_index = 0;
    size_t i = 0;

    k_smallest_value = QUICK__randomized_select(arr, 0, length, k);

    // find the index of th k smallest item
    for(; arr[k_smallest_value_index] != k_smallest_value; ++k_smallest_value_index);

    retval = QUICK__quicktsort(arr, 0, k_smallest_value_index);
    if(SUCCESS != retval) {
        goto l_cleanup;
    }

    // print results
    (void)printf("Quick (%zu): ", g_quick_cmp_count);
    for(i = 0; i < k; ++i) {
        (void)printf("%d ", arr[i]);
    }
    (void)printf("\n");

    retval = SUCCESS;
l_cleanup:
    return retval;
}

/**
 * Run the min-heap based method.
 * Will first use the 'build-min-heap' algorithm the create a min-heap.
 * Then, use heap-extract-min to extract items.
 * @param values_to_extract: the amount of values to extract
 * @param length: length of the array
 * @param arr: The array to operate on
 */
static
void
run_heap(size_t values_to_extract, size_t length, int *arr) {
    int min = 0;

    HEAP__build_min_heap(arr, (length));

    (void)printf("Heap (%zu): ", g_heap_cmp_count);
    for (size_t i = 0; i < values_to_extract; ++i) {
        HEAP__extract_min(arr, &length, &min);
        printf("%d ", min);
    }

    (void)printf("\n");
}

int main(int argc, char *argv[]) {
    retval_t retval = UNINITIALIZED;
    size_t values_to_extract = 0;
    size_t amount_of_values = 0;
    int *arr = NULL;
    int *heap_arr = NULL;
    int *quick_arr = NULL;
    size_t arr_size = 0;

    // validate command line input
    if(argc != 3) {
        fprintf(stderr, "Usage: %s N K\n", argv[0]);
        fprintf(stderr, "N - number of values in input, K - number of min values to extract\n");
        retval = INVALID_PARAMETERS;
        goto l_cleanup;
    }

    errno = 0;
    values_to_extract = strtol(argv[2], NULL, 10);
    amount_of_values = strtol(argv[1], NULL, 10);
    if (errno != 0) {
        retval = INVALID_PARAMETERS;
        goto l_cleanup;
    }

    initialize_array(amount_of_values, &arr);

    // duplicate arrays
    arr_size = sizeof(*arr) * amount_of_values;
    heap_arr = (int *)malloc(arr_size);
    quick_arr = (int *)malloc(arr_size);
    if (heap_arr == NULL || quick_arr == NULL) {
        retval = MAIN__FAILED_ALLOCATION_ARRAY;
        goto l_cleanup;
    }
    (void)memcpy(heap_arr, arr, arr_size);
    (void)memcpy(quick_arr, arr, arr_size);

    run_heap(values_to_extract, amount_of_values, arr);
    run_quick(values_to_extract, amount_of_values, quick_arr);

    retval = SUCCESS;

l_cleanup:
    SAFE_FREE(arr);
    SAFE_FREE(quick_arr);
    SAFE_FREE(heap_arr);

    return retval;
}
