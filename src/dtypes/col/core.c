#include <stdlib.h>
#include <string.h>
#include "core/internal.h"
#include "dtypes/col/core.h"
#include "dtypes/col/core/enum.h"
#include "dtypes/col/core/internal.h"

/* lifecycle */

col_t *col_from_array(
    const char *name,
    const void *data, 
    const size_t n_rows, 
    const col_dtype_t dtype,
    int *err_out
) {
    /* arg checks */
    if (!data || !n_rows)
        return mlc_fail(err_out, COL_NO_DATA);

    /* allocation */
    const size_t dtype_size = col_dtype_size(dtype);
    if (dtype_size == SIZE_MAX)
        return mlc_fail(err_out, COL_INVALID_DTYPE);

    struct col *col = malloc(sizeof(struct col));
    if (!col)
        return mlc_fail(err_out, COL_OOM);

    col->name = NULL;
    col->data = NULL;
    col->n_rows = 0;
    col->dtype = 0;

    const size_t n_bytes = n_rows * dtype_size;
    col->data = malloc(n_bytes);
    if (!col->data)
        goto fail;

    col->name = strdup(name);
    if (!col->name)
        goto fail;

    /* assignment */
    if (dtype != COL_DTYPE_STR) {
        memcpy(col->data, data, n_bytes);
    } else {
        char **src = (char **)data;
        char **dst = (char **)col->data;
        for (size_t i = 0; i < n_rows; i++) {
            dst[i] = strdup(src[i]);
            if (!dst[i])
                goto fail;
        }
    }

    col->n_rows = n_rows;
    col->dtype = dtype;

    if (err_out)
        *err_out = COL_OK;
    return col;
    
    /* error paths */
fail:
    col_free(col);
    return mlc_fail(err_out, COL_OOM);
}

col_t *col_clone(const col_t *col, int *err_out) {
    /* arg checks */
    const enum col_err err = col_validate(col, 0);
    if (err)
        return mlc_fail(err_out, err);

    /* allocation */
    struct col *new_col = malloc(sizeof(struct col));
    if (!new_col)
        return mlc_fail(err_out, COL_OOM);

    new_col->data = NULL;
    new_col->name = NULL;
    new_col->n_rows = 0;
    new_col->dtype = 0;

    const size_t dtype_size = col_dtype_size(col->dtype);
    const size_t n_bytes = col->n_rows * dtype_size;
    new_col->data = malloc(n_bytes);
    if (!new_col->data)
        goto fail;

    new_col->name = strdup(col->name);
    if (!new_col->name)
        goto fail;

    /* assignment */
    if (col->dtype != COL_DTYPE_STR) {
        memcpy(new_col->data, col->data, n_bytes);
    } else {
        char **src = (char **)col->data;
        char **dst = (char **)new_col->data;
        for (size_t i = 0; i < col->n_rows; i++) {
            dst[i] = strdup(src[i]);
            if (!dst[i])
                goto fail;
        }
    }

    new_col->n_rows = col->n_rows;
    new_col->dtype = col->dtype;

    if (err_out)
        *err_out = COL_OK;
    return new_col;
    
    /* error paths */
fail:
    col_free(new_col);
    return mlc_fail(err_out, COL_OOM);
}

int col_free(col_t *col) {
    if (!col)
        return COL_OK;

    if (col->name)
        free(col->name);

    if (col->data) {
        if (col->dtype == COL_DTYPE_STR) {
            char **str_arr = (char **)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                if (str_arr[i])
                    free(str_arr[i]);
        }

        free(col->data);
    }

    free(col);

    return COL_OK;
}

/* access */ 

void *col_at(const col_t *col, const size_t idx, int *err_out) {
    /* args check */
    const enum col_err err = col_validate(col, idx);
    if (err)
        return mlc_fail(err_out, err);

    const size_t dtype_size = col_dtype_size(col->dtype);

    if (err_out)
        *err_out = COL_OK;
    return (char *)col->data + (idx * dtype_size);
}

/* modification */

int col_set(col_t *col, const size_t idx, const void *val) {
    /* args check */
    const enum col_err err = col_validate(col, idx);
    if (err)
        return err;

    if (col->dtype == COL_DTYPE_STR) {
        free(((char **)col->data)[idx]);
        ((char **)col->data)[idx] = strdup((char *)val);
        if (!((char **)col->data)[idx])
            return COL_OOM;
    } else {
        const size_t dtype_size = col_dtype_size(col->dtype);
        memcpy((char *)col->data + (idx * dtype_size), val, dtype_size);
    }

    return COL_OK;
}
int col_push(col_t *col, const void *val);
int col_pop(col_t *col, const size_t idx);
