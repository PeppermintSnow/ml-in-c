#ifndef COL_CORE_INTERNAL_H
#define COL_CORE_INTERNAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dtypes/col/core/type.h"

static size_t col_dtype_strides[] = {
    [COL_DTYPE_DOUBLE] = sizeof(double),
    [COL_DTYPE_FLOAT] = sizeof(float),
    [COL_DTYPE_INT64] = sizeof(int64_t),
    [COL_DTYPE_INT32] = sizeof(int32_t),
    [COL_DTYPE_UINT8] = sizeof(uint8_t),
    [COL_DTYPE_STRING] = sizeof(char *)
};

static size_t col_dtype_strides_len = (
    sizeof(col_dtype_strides) / sizeof(col_dtype_strides[0])
);

/* THIS FUNCTION ASSUMES DTYPE IS WITHIN BOUNDS */
static inline size_t col_dtype_stride(const col_dtype_t dtype) {
    return col_dtype_strides[dtype];
}

static inline int col_dtype_validate(const col_dtype_t dtype) {
    return dtype >= col_dtype_strides_len;
}

#endif
