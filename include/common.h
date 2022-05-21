#pragma once

#define ARRAY_LENGTH(_arr)  ((sizeof((_arr))) / (sizeof((*_arr))))

#define SAFE_FREE(_ptr) \
do { \
    if(NULL != (_ptr)) { \
        free((_ptr));    \
        _ptr = NULL;     \
    }                    \
} while(0)


/**
 * Swap two values.
 * @param a: first value to swap
 * @param b: second value to swap
 * @param arr: The array to operate on
 */
void
COMMON__swap_int(int *a, int *b);
