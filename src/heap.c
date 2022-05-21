#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "common.h"
#include "retvals.h"

size_t g_heap_cmp_count = 0;

/**
 * Heapify the heap according to the heapify algorithm.
 * @param heap: the heap to heapify
 * @param heap_size : number of elements in the heap
 * @param root_index: the index of the root we currently heapify-ing
 */
static
void
heapify(int heap[], size_t heap_size, int root_index) {
    int smallest = root_index; // initialize smallest as root
    int left = (2 * root_index) + 1; // left = 2*i + 1
    int right = (2 * root_index) + 2; // right = 2*i + 2

    assert(NULL != heap);

    // if left child is less than root
    if (left < heap_size && heap[left] < heap[smallest])
        smallest = left;

    // if right child is less than smallest so far
    if (right < heap_size && heap[right] < heap[smallest])
        smallest = right;

    // if smallest is not root
    if (smallest != root_index) {
        COMMON__swap_int(&heap[root_index], &heap[smallest]);

        // recursively heapify the affected sub-tree
        heapify(heap, heap_size, smallest);
    }

    // count comparisons
    g_heap_cmp_count += 3;
}

/**
 * Builds a heap according to the build-min-heap algorithm.
 * @param heap: heap array we will be building.
 * @param heap_size : number of elements in the heap
 * @return: SUCCESS if successful, otherwise an appropriate status code
 */
retval_t
HEAP__build_min_heap(int heap[], size_t heap_size) {
    retval_t retval = UNINITIALIZED;
    size_t start_index = (heap_size / 2) - 1;

    if(NULL == heap) {
       retval = INVALID_PARAMETERS;
       goto l_cleanup;
    }

    for(int i = (int)start_index; i >= 0; --i) {
        heapify(heap, heap_size, i);
    }

    retval = SUCCESS;

l_cleanup:
    return retval;
}

/**
 * Extracts the samllest number from the heap, and re-heapifies the heap
 * @param heap: heap we will be extracting from.
 * @param heap_size : number of elements in the heap
 * @param min: store minimum value of the heap here
 * @return: SUCCESS if successful, otherwise an appropriate status code
 */
retval_t
HEAP__extract_min(int heap[], size_t *heap_size, int *min) {
    retval_t retval = UNINITIALIZED;
    size_t internal_heap_size = *heap_size;
    int internal_min = 0;

    if(NULL == heap) {
        retval = UNINITIALIZED;
        goto l_cleanup;
    }

    internal_min = heap[0];
    heap[0] = heap[internal_heap_size - 1];
    --internal_heap_size;

    heapify(heap, internal_heap_size, 0);

    // transfer of ownership
    *min = internal_min;
    *heap_size = internal_heap_size;

    retval = SUCCESS;

l_cleanup:
    return retval;
}
