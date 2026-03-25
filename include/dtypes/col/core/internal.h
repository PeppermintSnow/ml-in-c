#ifndef COL_CORE_INTERNAL_H
#define COL_CORE_INTERNAL_H

#include <stdint.h>
#include <string.h>
#include "dtypes/col/core/struct.h"
#include "dtypes/col/core/enum.h"

static const size_t col_dtype_ltbl[] = {
    [COL_DTYPE_DOUBLE]   =   sizeof(double),
    [COL_DTYPE_INT]      =   sizeof(int),
    [COL_DTYPE_UINT8]    =   sizeof(uint8_t),
    [COL_DTYPE_STR]      =   sizeof(char *)
};

static const size_t col_dtype_ltbl_len = (
    sizeof(col_dtype_ltbl) / sizeof(*col_dtype_ltbl)
);

static inline size_t col_dtype_size(col_dtype_t dtype) {
    if (dtype >= col_dtype_ltbl_len)
        return SIZE_MAX;
    return col_dtype_ltbl[dtype];
}

static inline int col_validate(const col_t *col, const size_t idx) {
    if (!col || !col->data || !col->n_rows || !col->name)
        return COL_NO_DATA;
    if (col->dtype >= col_dtype_ltbl_len)
        return COL_INVALID_DTYPE;
    if (idx >= col->n_rows)
        return COL_OUT_OF_BOUNDS;
    return COL_OK;
}

#endif
