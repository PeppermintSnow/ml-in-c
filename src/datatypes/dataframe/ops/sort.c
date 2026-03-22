#include <stdio.h>
#include <string.h>
#include "datatypes/dataframe/ops/sort_internal.h"

int df_sort(
    dataframe_t *df, 
    const char *col, 
    const df_sort_order order
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return DF_NO_COL;

    size_t stack[df->n_rows];
    size_t top = 0;

    stack[top++] = 0;
    stack[top++] = df->n_rows - 1;

    while (top > 0) {
        size_t high = stack[--top];
        size_t low = stack[--top];

        size_t pivot_index = partition(df, low, high, col_idx, order);

        if (pivot_index > low) {
            stack[top++] = low;
            stack[top++] = pivot_index - 1;
        }

        if (pivot_index < high) {
            stack[top++] = pivot_index + 1;
            stack[top++] = high;
        }
    }

    return DF_OK;
}
