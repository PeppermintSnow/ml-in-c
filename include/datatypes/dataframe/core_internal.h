#ifndef DATAFRAME_CORE_INTERNAL_H
#define DATAFRAME_CORE_INTERNAL_H

#include <stddef.h>
#include <string.h>
#include <math.h>

static inline size_t df_col_idx( const dataframe_t *df, const char *col) {
    for (size_t i = 0; i < df->n_cols; i++)
        if (strcmp(df->columns[i], col) == 0)
            return i;
    return (size_t)-1;
}

static inline void *df_fail(int *err_out, int err_code) {
    if (err_out)
        *err_out = err_code;
    return NULL;
}

static inline double df_fail_nan(int *err_out, int err_code) {
    if (err_out)
        *err_out = err_code;
    return NAN;
}

#endif
