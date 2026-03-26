#ifndef MLC_CORE_ERROR_H
#define MLC_CORE_ERROR_H

#include <math.h>
#include <stdlib.h>

#ifdef MLC_ABORT_ON_ERROR
#define MLC_ABORT() abort()
#else
#define MLC_ABORT() do { } while (0)
#endif

static inline void *mlc_fail_null(int err_code, int *err_out) {
    if (err_out)
        *err_out = err_code;
    MLC_ABORT();
    return NULL;
}

static inline double mlc_fail_nan(int err_code, int *err_out) {
    if (err_out)
        *err_out = err_code;
    MLC_ABORT();
    return NAN;
}

#endif
