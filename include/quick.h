#pragma once

#include "retvals.h"

extern size_t  g_quick_cmp_count;

/**
 * Implements the randomized-select algorithm
 * @param arr: the (sub-)array to operate on
 * @param start: start index
 * @param end : end index
 * @param k : which minimum number to pick
 * @return the k-th smallest value.
 */
int
QUICK__randomized_select(int arr[], size_t start, size_t end, size_t k);

/**
 * Implements the randomized-select algorithm
 * @param arr: the (sub-)array to operate on
 * @param start: start index
 * @param end : end index
* @return: SUCCESS if successful, otherwise an appropriate status code
 */
void
QUICK__quicksort(int arr[], size_t start, size_t end);
