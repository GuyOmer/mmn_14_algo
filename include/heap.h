#pragma once

extern size_t g_heap_cmp_count;

/**
 * Implements the build-heap-min algorithm
 * @param heap: the heap to build, represented by an array
 * @param heap_size: number of elements in the heap
 * @return SUCCESS if successful, otherwise an appropriate status code
 */
retval_t
HEAP__build_min_heap(int heap[], size_t heap_size);

/**
 * Extracts the samllest number from the heap, and re-heapifies the heap
 * @param heap: heap we will be extracting from.
 * @param heap_size : number of elements in the heap
 * @param min: store minimum value of the heap here
 * @return: SUCCESS if successful, otherwise an appropriate status code
 */
retval_t
HEAP__extract_min(int heap[], size_t *heap_size, int *min);
