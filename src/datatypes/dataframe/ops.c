#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/core_internal.h"
#include <stdio.h>
#include <stdlib.h>
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
