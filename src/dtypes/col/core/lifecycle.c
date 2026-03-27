#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "core/error.h"
#include "dtypes/col/core/type.h"
#include "dtypes/col/core/lifecycle.h"
#include "dtypes/col/core/internal.h"

static col_err_t col_args_validate(
    const char *name,
    const void *data, 
    const size_t n_rows, 
    const col_dtype_t dtype,
    const int require_data
) {
    if (col_dtype_validate(dtype))
        return COL_ERR_INVALID_DTYPE;
    if (!name || !strlen(name))
        return COL_ERR_EMPTY_NAME;
    if (require_data && (!n_rows || !data))
        return COL_ERR_NO_DATA;
    return COL_ERR_OK;
}

/* THIS FUNCTION ASSUMES ITS PARAMETERS ARE VALIDD */
static col_t *col_init(
    const char *name, 
    const size_t n_rows,
    const col_dtype_t dtype
) {
    const size_t stride = col_dtype_stride(dtype);

    /* alloc */
    struct col *col = NULL;
    void *tmp_data = NULL;
    char *tmp_name = NULL;

    col = malloc(sizeof(struct col));
    if (!col)
        goto fail;

    tmp_data = n_rows ? malloc(n_rows * stride) : NULL;
    if (!tmp_data && n_rows)
        goto fail;

    tmp_name = strdup(name);
    if (!tmp_name)
        goto fail;

    /* init */
    struct col tmp_col = { 
        tmp_name, 
        tmp_data, 
        n_rows, 
        dtype, 
        stride 
    };
    memcpy(col, &tmp_col, sizeof(struct col));

    return col;

fail:
    if (col)
        free(col);
    if (tmp_data)
        free(tmp_data);
    if (tmp_name)
        free(tmp_name);
    return NULL;
}

static int col_data_fill(col_t *col, const void *data){
    if (col->dtype == COL_DTYPE_STRING) {
        const char **src = (const char **)data;
        char **dst = col->data;
        for (size_t i = 0; i < col->n_rows; i++) {
            dst[i] = strdup(src[i]);
            if (!dst[i])
                return COL_ERR_OOM;
        }
    } else {
        memcpy(col->data, data, col->n_rows * col->stride);
    }

    return COL_ERR_OK;
}

col_t *col_create(
    const char *name,
    const col_dtype_t dtype,
    int *err_out
) {
    /* args */ 
    enum col_err err_code = col_args_validate(name, NULL, 0, dtype, 0);
    if (err_code)
        return mlc_fail_null(err_code, err_out);

    /* init */
    struct col *col = col_init(name, 0, dtype);
    if (!col)
        return mlc_fail_null(COL_ERR_OOM, err_out);

    return col;
}

col_t *col_create_array(
    const char *name,
    const void *data, 
    const size_t n_rows, 
    const col_dtype_t dtype,
    int *err_out
) {
    /* args */ 
    enum col_err err_code = col_args_validate(name, data, n_rows, dtype, 1);
    if (err_code)
        return mlc_fail_null(err_code, err_out);

    /* init */ 
    struct col *col = col_init(name, n_rows, dtype);
    if (!col)
        return mlc_fail_null(COL_ERR_OOM, err_out);

    /* assign */
    err_code = col_data_fill(col, data);
    if (err_code) {
        col_free(col);
        return mlc_fail_null(err_code, err_out);
    }

    return col;
}

col_t *col_clone(const col_t *col, int *err_out) {
    /* args */
    if (!col)
        return mlc_fail_null(COL_ERR_NO_DATA, err_out);

    enum col_err err_code = col_args_validate(
        col->name, 
        col->data, 
        col->n_rows, 
        col->dtype, 
        1
    );
    if (err_code)
        return mlc_fail_null(err_code, err_out);

    /* alloc */
    err_code = COL_ERR_OOM;

    struct col *new_col = NULL;
    char *tmp_name = NULL;
    void *tmp_data = NULL;

    new_col = malloc(sizeof(struct col));
    if (!new_col)
        goto fail;

    tmp_data = col->n_rows ? malloc(col->n_rows * col->stride) : NULL;
    if (!tmp_data && col->n_rows)
        goto fail;

    tmp_name = strdup(col->name);
    if (!tmp_name)
        goto fail;

    /* assign */
    memcpy(new_col, col, sizeof(struct col));
    new_col->name = tmp_name;
    new_col->data = tmp_data;

    tmp_name = NULL;
    tmp_data = NULL;

    err_code = col_data_fill(new_col, col->data);
    if (err_code)
        goto fail;

    return new_col;

fail:
    if (new_col)
        col_free(new_col);
    if (tmp_data)
        free(tmp_data);
    if (tmp_name)
        free(tmp_name);
    return mlc_fail_null(err_code, err_out);
}

int col_free(col_t *col) {
    if (!col)
        return COL_ERR_NO_DATA;

    if (col->name)
        free(col->name);

    if (col->data) {
        if (col->dtype == COL_DTYPE_STRING) {
            char **data = col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                if (data[i])
                    free(data[i]);
        }
        free(col->data);
    }

    free(col);

    return COL_ERR_OK;
}
