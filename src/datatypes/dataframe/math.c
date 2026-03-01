#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/core_internal.h"
#include "../../../include/datatypes/dataframe/math_internal.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double *df_col_add(
	const dataframe_t *df,
    const char *col1,
    const char *col2,
    int *err_out
) {
    return df_col_arithmetic(df, col1, col2, '+', err_out);
}

double *df_col_sub(
	const dataframe_t *df,
    const char *col1,
    const char *col2,
    int *err_out
) {
    return df_col_arithmetic(df, col1, col2, '-', err_out);
}

double *df_col_mul(
	const dataframe_t *df,
	const char *col1,
	const char *col2,
	int *err_out
) {
    return df_col_arithmetic(df, col1, col2, '*', err_out);
}

double *df_col_div(
	const dataframe_t *df,
	const char *col1,
	const char *col2,
	int *err_out
) {
    return df_col_arithmetic(df, col1, col2, '/', err_out);
}

double *df_col_add_s(
	const dataframe_t *df,
	const char *col,
	const double scalar,
	int *err_out
) {
    return df_col_arithmetic_s(df, col, scalar, '+', err_out);
}

double *df_col_sub_s(
	const dataframe_t *df,
	const char *col,
	const double scalar,
	int *err_out
) {
    return df_col_arithmetic_s(df, col, scalar, '-', err_out);
}

double *df_col_mul_s(
	const dataframe_t *df,
	const char *col,
	const double scalar,
	int *err_out
) {
    return df_col_arithmetic_s(df, col, scalar, '*', err_out);
}

double *df_col_div_s(
	const dataframe_t *df,
	const char *col,
	const double scalar,
	int *err_out
) {
    return df_col_arithmetic_s(df, col, scalar, '/', err_out);
}

double df_col_mean(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);

    double mean = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        mean += df->data[r * df->n_cols + col_idx];
    mean /= df->n_rows;

    if (err_out)
        *err_out = DF_OK;
    return mean;
}

double df_col_sum(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);

    double sum = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        sum += df->data[r * df->n_cols + col_idx];

    if (err_out)
        *err_out = DF_OK;
    return sum;
}

double df_col_min(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);

    double min = df->data[col_idx];
    for (size_t r = 1; r < df->n_rows; r++)
        if (min > df->data[r * df->n_cols + col_idx])
            min = df->data[r * df->n_cols + col_idx];

    if (err_out)
        *err_out = DF_OK;
    return min;
}

double df_col_max(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);

    double max = df->data[col_idx];
    for (size_t r = 1; r < df->n_rows; r++)
        if (max < df->data[r * df->n_cols + col_idx])
            max = df->data[r * df->n_cols + col_idx];

    if (err_out)
        *err_out = DF_OK;
    return max;
}

double df_col_var(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);
    
    double mean = df_col_mean(df, col, NULL);
    double var = 0;
    
    for (size_t r = 0; r < df->n_rows; r++)
        var += pow(df->data[r * df->n_cols + col_idx] - mean, 2);
    var /= df->n_rows;

    if (err_out)
        *err_out = DF_OK;
    return var;
}

double df_col_std(
	const dataframe_t *df,
	const char *col,
	int *err_out
) {
    size_t col_idx = df_col_idx(df, col);
    if (col_idx == (size_t)-1)
        return df_fail_nan(err_out, DF_NO_COL);

    if (err_out)
        *err_out = DF_OK;
    return sqrt(df_col_var(df, col, err_out));
}
