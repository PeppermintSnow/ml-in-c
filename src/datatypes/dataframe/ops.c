#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/core_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/datatypes/dataframe/ops.h"

static inline uint8_t apply_condition(
    const double data, 
    const double val, 
    const df_mask_comparison_t op
) {
    switch (op) {
        case DF_MASK_EQ: return (data == val) ? 0xFF : 0x00;
        case DF_MASK_NE: return (data != val) ? 0xFF : 0x00;
        case DF_MASK_LT: return (data < val) ? 0xFF : 0x00;
        case DF_MASK_LE: return (data <= val) ? 0xFF : 0x00;
        case DF_MASK_GT: return (data > val) ? 0xFF : 0x00;
        case DF_MASK_GE: return (data >= val) ? 0xFF : 0x00;
    }   
    return 0x00;
}

df_mask_t *df_mask_create(const int n_rows, int *err_out) {
    struct df_mask *mask = malloc(sizeof(struct df_mask));
    if (!mask)
        return df_fail(err_out, DF_OOM);

    mask->data = malloc(n_rows * sizeof(uint8_t));
    if (!mask->data)
        return df_fail(err_out, DF_OOM);

    mask->n_rows = n_rows;
    mask->n_keep = n_rows;
    memset(mask->data, 0xFF, n_rows);

    if (err_out)
        *err_out = DF_OK;
    return mask;
}

int df_mask_or(
	df_mask_t *mask,
    const dataframe_t *df,
	const char *col,
	const df_mask_comparison_t comp,
	const double value
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return DF_NO_COL;

    if (mask->n_rows != df->n_rows)
        return DF_ROW_MISMATCH;

    size_t tmp_n = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        mask->data[r] |= apply_condition(
            df->data[r * df->n_cols + col_idx], 
            value, 
            comp
        );
        if (mask->data[r])
            tmp_n++;
    }

    mask->n_keep = tmp_n;

    return DF_OK;
}

int df_mask_and(
	df_mask_t *mask,
    const dataframe_t *df,
	const char *col,
	const df_mask_comparison_t comp,
	const double value
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return DF_NO_COL;

    if (mask->n_rows != df->n_rows)
        return DF_ROW_MISMATCH;

    size_t tmp_n = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        if (mask->data[r]) {
            mask->data[r] &= apply_condition(
                df->data[r * df->n_cols + col_idx], 
                value, 
                comp
            );
            if (mask->data[r])
                tmp_n++;
        }
    }

    mask->n_keep = tmp_n;

    return DF_OK;
}

int df_mask_apply(dataframe_t *df, const df_mask_t *mask) {
    if (mask->n_rows != df->n_rows)
        return DF_ROW_MISMATCH;

    double *tmp = malloc(mask->n_keep * df->n_cols * sizeof(double));
    if (!tmp)
        return DF_OOM;

    size_t tmp_idx = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        if (mask->data[r] == 0x00)
            continue;

        memcpy(
            &tmp[tmp_idx * df->n_cols],
            &df->data[r * df->n_cols],
            df->n_cols * sizeof(*df->data)
        );
        tmp_idx++;
    }

    free(df->data);
    df->data = tmp;
    df->n_rows = mask->n_keep;

    return DF_OK;
}

int df_mask_free(df_mask_t *mask) {
    if (mask->data)
        free(mask->data);
    if (mask)
        free(mask);
    return DF_OK;
}

dataframe_t *df_clone(const dataframe_t *df, int *err_out) {
    struct dataframe *clone_df = malloc(sizeof(struct dataframe));
    if (!clone_df)
        return df_fail(err_out, DF_OOM);

    size_t nbytes_data = df->n_rows * df->n_cols * sizeof(*df->data);
    clone_df->data = malloc(nbytes_data);
    if (!clone_df->data)
        goto fail;

    clone_df->columns = malloc(df->n_cols * sizeof(*df->columns));
    if (!clone_df->columns)
        goto fail;

    for (size_t i = 0; i < df->n_cols; i++) {
        clone_df->columns[i] = strdup(df->columns[i]);
        if (!clone_df->columns[i])
            goto fail;
    }

    memcpy(clone_df->data, df->data, nbytes_data);
    clone_df->n_rows = df->n_rows;
    clone_df->n_cols = df->n_cols;

    if (err_out)
        *err_out = DF_OK;
    return clone_df;

fail:
    df_free(clone_df);
    return df_fail(err_out, DF_OOM);
}

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
