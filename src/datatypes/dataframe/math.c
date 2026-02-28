#include "../../../include/datatypes/dataframe/core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *df_col_add(dataframe_t *df, const char *col1, const char *col2) {
    ssize_t col1_idx = -1, col2_idx = -1;
    for (size_t i = 0; i < df->n_cols; i++) {
        if (col1_idx == -1 && strcmp(df->columns[i], col1) == 0)
            col1_idx = i;
        if (col2_idx == -1 && strcmp(df->columns[i], col2) == 0)
            col2_idx = i;
        if (col1_idx != -1 && col2_idx != -1)
            break;
    }

    if (col1_idx == -1 || col2_idx == -1)
        return NULL;

    double *sum = malloc(df->n_rows * sizeof(double));
    if (!sum)
        return NULL;

    for (size_t r = 0; r < df->n_rows; r++)
        sum[r] = df->data[r * df->n_cols + col1_idx] 
            + df->data[r * df->n_cols + col2_idx];

    return sum;
}
