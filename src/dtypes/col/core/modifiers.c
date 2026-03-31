#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "core/error.h"
#include "dtypes/col/core/type.h"
#include "dtypes/col/core/modifiers.h"
#include "dtypes/col/core/internal.h"

int col_set(col_t *col, const void *val, const size_t idx) {
    /* args */
    if (idx >= col->n_rows)
        return COL_ERR_OUT_OF_BOUNDS;
    if (!val)
        return COL_ERR_NO_DATA;

    /* assign */
    if (col->dtype == COL_DTYPE_STRING) {
        char *buf = strdup(val);
        if (!buf)
            return COL_ERR_OOM;

        free(((char **)col->data)[idx]);
        ((char **)col->data)[idx] = buf;
    } else {
        memcpy((char *)col->data + (col->stride * idx), val, col->stride);
    }

    return COL_ERR_OK;
}

int col_append(col_t *col, const void *val) {
    /* args */
    if (!val)
        return COL_ERR_NO_DATA;

    /* malloc */
    char *strbuf = NULL;
    if (col->dtype == COL_DTYPE_STRING) {
        strbuf = strdup(val);
        if (!strbuf)
            goto fail_strbuf;
    }

    void *tmp_data = realloc(col->data, (col->n_rows + 1) * col->stride);
    if (!tmp_data)
        goto fail_tmp_data;

    /* assign */
    col->data = tmp_data;

    if (col->dtype == COL_DTYPE_STRING) 
        ((char **)col->data)[col->n_rows] = strbuf;
    else
        memcpy(
            (char *)col->data + (col->stride * col->n_rows),
            val,
            col->stride
        );

    col->n_rows += 1;

    return COL_ERR_OK;

fail_tmp_data:
fail_strbuf:
    free(strbuf);
    return COL_ERR_OOM;
}

int col_remove(col_t *col, const size_t idx) {
    /* args */
    if (idx >= col->n_rows)
        return COL_ERR_OUT_OF_BOUNDS;

    /* assign */
    if (col->dtype == COL_DTYPE_STRING)
        free(((char **)col->data)[idx]);

    memmove(
        (char *)col->data + (col->stride * idx),
        (char *)col->data + (col->stride * (idx + 1)),
        col->stride * (col->n_rows - idx - 1)
    );

    col->n_rows -= 1;

    if (col->n_rows == 0)
        return COL_ERR_OK;

    /* ?malloc */
    void *tmp_data = realloc(col->data, (col->n_rows) * col->stride);
    if (tmp_data)
        col->data = tmp_data;

    return COL_ERR_OK;
}

int col_rename(col_t *col, const char *name) {
    /* args */
    if (!name)
        return COL_ERR_EMPTY_NAME;

    /* malloc */
    char *tmp_name = strdup(name);
    if (!tmp_name)
        return COL_ERR_OOM;

    /* assign */
    free(col->name);
    col->name = tmp_name;

    return COL_ERR_OK;
}
