#include <stdlib.h>
#include <string.h>
#include "datatypes/dataframe/ops/select.h"

int df_col_select(dataframe_t *df, const char **cols, const size_t n_cols) {
    size_t col_idxs[n_cols];
    size_t match_idx = 0;
    for (size_t i = 0; i < df->n_cols; i++)
        for (size_t j = 0; j < n_cols; j++)
            if (strcmp(df->columns[i], cols[j]) == 0)
                col_idxs[match_idx++] = i;

    if (match_idx != n_cols)
        return DF_NO_COL;

    double *tmp_data = malloc(df->n_rows * n_cols * sizeof(*df->data));
    if (!tmp_data)
        return DF_OOM;

    char **tmp_cols = malloc(n_cols * sizeof(*df->columns));
    if (!tmp_cols)
        goto fail;

    for (size_t r = 0; r < df->n_rows; r++)
        for (size_t c = 0; c < n_cols; c++)
            tmp_data[r * n_cols + c] = df->data[r * df->n_cols + col_idxs[c]];

    for (size_t c = 0; c < n_cols; c++) {
        tmp_cols[c] = strdup(df->columns[col_idxs[c]]);
        if (!tmp_cols[c])
            goto fail;
    }

    free(df->data);
    for (size_t c = 0; c < df->n_cols; c++)
        free(df->columns[c]);
    free(df->columns);

    df->data = tmp_data;
    df->columns = tmp_cols;
    df->n_cols = n_cols;

    return DF_OK;

fail:
    if (tmp_data)
        free(tmp_data);
    if (tmp_cols) {
        for (size_t i = 0; i < n_cols; i++)
            if (tmp_cols[i])
                free(tmp_cols[i]);
        free(tmp_cols);
    }
    return DF_OOM;
}

int df_row_select(dataframe_t *df, const size_t start, const size_t end) {
    if (start > end)
        return DF_BAD_ARG;
    if (end > df->n_rows)
        return DF_NO_ROW;

    size_t n_rows = end - start;
    double *tmp_data = malloc(n_rows * df->n_cols * sizeof(*df->data));
    if (!tmp_data)
        return DF_OOM;

    memcpy(
        tmp_data, 
        &df->data[start * df->n_cols], 
        n_rows * df->n_cols * sizeof(*df->data)
    );

    free(df->data);
    df->data = tmp_data;
    df->n_rows = n_rows;

    return DF_OK;
}
