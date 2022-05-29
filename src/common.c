#include <stddef.h>
#include <assert.h>


void
COMMON__swap_int(int *a, int *b) {
    int temp = 0;

    assert(a != NULL && b != NULL);

    temp = *a;
    *a = *b;
    *b = temp;
}
