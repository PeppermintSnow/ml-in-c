#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/math_internal.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

double *df_col_add_s(dataframe_t *df, const char *col, const double scalar) {
    return df_col_arithmetic_s(df, col, scalar, '+');
}

double *df_col_sub_s(dataframe_t *df, const char *col, const double scalar) {
    return df_col_arithmetic_s(df, col, scalar, '-');
}

double *df_col_mul_s(dataframe_t *df, const char *col, const double scalar) {
    return df_col_arithmetic_s(df, col, scalar, '*');
}

double *df_col_div_s(dataframe_t *df, const char *col, const double scalar) {
    return df_col_arithmetic_s(df, col, scalar, '/');
}

double df_col_mean(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;

    double mean = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        mean += df->data[r * df->n_cols + col_idx];
    mean /= df->n_rows;

    return mean;
}

double df_col_sum(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;

    double sum = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        sum += df->data[r * df->n_cols + col_idx];

    return sum;
}

double df_col_min(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;

    double min = df->data[col_idx];
    for (size_t r = 1; r < df->n_rows; r++)
        if (min > df->data[r * df->n_cols + col_idx])
            min = df->data[r * df->n_cols + col_idx];

    return min;
}

double df_col_max(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;

    double max = df->data[col_idx];
    for (size_t r = 1; r < df->n_rows; r++)
        if (max < df->data[r * df->n_cols + col_idx])
            max = df->data[r * df->n_cols + col_idx];

    return max;
}

double df_col_var(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;
    
    double mean = df_col_mean(df, col);
    double var = 0;
    
    for (size_t r = 0; r < df->n_rows; r++)
        var += pow(df->data[r * df->n_cols + col_idx] - mean, 2);
    var /= df->n_rows;

    return var;
}

double df_col_std(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return NAN;

    return sqrt(df_col_var(df, col));
}
