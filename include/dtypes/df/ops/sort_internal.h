#ifndef DATAFRAME_SORT_INTERNAL_H
#define DATAFRAME_SORT_INTERNAL_H

#include "../core_internal.h"
#include "./sort.h"

static inline void swap(dataframe_t *df, size_t row1_idx, size_t row2_idx) {
    size_t row_bytes = df->n_cols * sizeof(*df->data);

    double tmp_row[df->n_cols];
    memcpy(tmp_row, &df->data[row1_idx * df->n_cols], row_bytes);

    memcpy(&df->data[row1_idx * df->n_cols], &df->data[row2_idx * df->n_cols], row_bytes);
    memcpy(&df->data[row2_idx * df->n_cols], tmp_row, row_bytes);
}

static inline int cmp(double a, double b, df_sort_order_t order) {
    return order == DF_SORT_ASC ? (a < b) : (a > b);
}

static inline size_t partition(
    dataframe_t *df,
	size_t low,
	size_t high,
	size_t col_idx,
	df_sort_order_t order
) {
    double pivot = df->data[high * df->n_cols + col_idx];

    size_t new_pivot_index = low;
    for (size_t j = low; j < high; j++)
        if (cmp(df->data[j * df->n_cols + col_idx], pivot, order))
            swap(df, new_pivot_index++, j);

    swap(df, new_pivot_index, high);
    return new_pivot_index;
}


#endif
