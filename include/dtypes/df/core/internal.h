#ifndef DATAFRAME_CORE_INTERNAL_H
#define DATAFRAME_CORE_INTERNAL_H

#include <stdint.h>
#include <string.h>
#include <math.h>
#include "dtypes/df/core/enum.h"

static inline size_t df_col_size(df_col_type_t dtype) {
    switch (dtype) {
        case DF_COL_TYPE_DOUBLE: return sizeof(double);
        case DF_COL_TYPE_INT:    return sizeof(int);
        case DF_COL_TYPE_UINT8:  return sizeof(uint8_t);
        case DF_COL_TYPE_STR:    return sizeof(char *);
    }
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
