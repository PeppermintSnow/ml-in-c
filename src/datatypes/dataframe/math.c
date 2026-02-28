#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * inline helper to comply with DRY
 */
static inline double *df_col_arithmetic(
    dataframe_t *df, 
    const char *col1, 
    const char *col2,
    char operation
) {
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

    double *res = malloc(df->n_rows * sizeof(double));
    if (!res)
        return NULL;

    for (size_t r = 0; r < df->n_rows; r++) {
        double a = df->data[r * df->n_cols + col1_idx];
        double b = df->data[r * df->n_cols + col2_idx];
        switch (operation) {
            case '+':
                res[r] = a + b;
                break;
            case '-':
                res[r] = a - b;
                break;
            case '*':
                res[r] = a * b;
                break;
            case '/':
                res[r] = b == 0 ? 0 : a / b;
                break;
        }
    }

    return res;
}

double *df_col_add(dataframe_t *df, const char *col1, const char *col2) {
    return df_col_arithmetic(df, col1, col2, '+');
}

double *df_col_sub(dataframe_t *df, const char *col1, const char *col2) {
    return df_col_arithmetic(df, col1, col2, '-');
}

double *df_col_mul(dataframe_t *df, const char *col1, const char *col2) {
    return df_col_arithmetic(df, col1, col2, '*');
}

double *df_col_div(dataframe_t *df, const char *col1, const char *col2) {
    return df_col_arithmetic(df, col1, col2, '/');
}
