#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include <stdlib.h>

static inline void *mlc_fail(int *err_out, int err_code) {
    if (err_out)
        *err_out = err_code;
#ifdef MLC_ABORT_ON_ERROR
    abort();
#endif
    return NULL;
}

#endif
