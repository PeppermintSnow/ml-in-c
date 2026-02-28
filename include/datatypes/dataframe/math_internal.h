#ifndef DATAFRAME_MATH_H
#define DATAFRAME_MATH_H

#include "./core.h"
#include <stdlib.h>
#include <string.h>

static inline size_t df_col_idx(
    const dataframe_t *df,
    const char *col
) {
    for (size_t i = 0; i < df->n_cols; i++)
        if (strcmp(df->columns[i], col) == 0)
            return i;
    return (size_t)-1;
}

/**
 * inline col-to-col helper to comply with DRY
 */
static inline double *df_col_arithmetic(
    dataframe_t *df, 
    const char *col1, 
    const char *col2,
    char operation
) {
    size_t col1_idx = df_col_idx(df, col1);
    size_t col2_idx = df_col_idx(df, col2);
    if (col1_idx == (size_t)-1 || col2_idx == (size_t)-1)
        return NULL;

    double *res = malloc(df->n_rows * sizeof(double));
    if (!res)
        return NULL;

    for (size_t r = 0; r < df->n_rows; r++) {
        double a = df->data[r * df->n_cols + col1_idx];
        double b = df->data[r * df->n_cols + col2_idx];
        switch (operation) {
            case '+': res[r] = a + b; break;
            case '-': res[r] = a - b; break;
            case '*': res[r] = a * b; break;
            case '/': res[r] = b == 0 ? 0 : a / b; break;
        }
    }

    return res;
}

/**
 * inline col-to-scalar helper to comply with DRY
 */
static inline double *df_col_arithmetic_s(
    dataframe_t *df, 
    const char *col, 
    double scalar,
    char operation
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NULL;

    double *res = malloc(df->n_rows * sizeof(double));
    if (!res)
        return NULL;

    for (size_t r = 0; r < df->n_rows; r++) {
        double a = df->data[r * df->n_cols + col_idx];
        switch (operation) {
            case '+': res[r] = a + scalar; break;
            case '-': res[r] = a - scalar; break;
            case '*': res[r] = a * scalar; break;
            case '/': res[r] = scalar == 0 ? 0 : a / scalar; break;
        }
    }

    return res;
}

#endif
