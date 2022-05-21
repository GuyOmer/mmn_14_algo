#pragma once

typedef enum retval_e {
    SUCCESS = 0,
    UNINITIALIZED,
    INVALID_PARAMETERS,

    // main
    MAIN__FAILED_ALLOCATION_ARRAY,

} retval_t;
