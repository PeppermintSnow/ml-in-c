#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

dataframe_t *generate_dummy_df(size_t n);

void test_df_col_arithmetic(
    double *(*df_func)(const dataframe_t *, const char *, const char *, int *), 
    double (*func)(double, double)
);

void test_df_col_arithmetic_s(
    double *(*df_func)(const dataframe_t *, const char *, const double, int *), 
    double (*func)(double, double)
);

void test_df_col_sum();
void test_df_col_mean();
void test_df_col_min();
void test_df_col_max();
void test_df_col_var();
void test_df_col_std();

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divi(double a, double b) { 
    return b == 0 ? 0 : a / b; 
}

int main() {
    test_df_col_arithmetic(df_col_add, add);
    test_df_col_arithmetic(df_col_sub, sub);
    test_df_col_arithmetic(df_col_mul, mul);
    test_df_col_arithmetic(df_col_div, divi);

    test_df_col_arithmetic_s(df_col_add_s, add);
    test_df_col_arithmetic_s(df_col_sub_s, sub);
    test_df_col_arithmetic_s(df_col_mul_s, mul);
    test_df_col_arithmetic_s(df_col_div_s, divi);

    test_df_col_sum();
    test_df_col_mean();
    test_df_col_min();
    test_df_col_max();
    test_df_col_var();
    test_df_col_std();
}

dataframe_t *generate_dummy_df(size_t n) {
    double foo[n], bar[n], baz[n];
    for (size_t i = 0; i < n; i++) {
        foo[i] = i;
        bar[i] = i * 2;
        baz[i] = i * 3;
    }

    int err;
    dataframe_t *df = df_from_array(foo, n, "foo", &err);
    assert(err == DF_OK);

    assert(df_col_append(df, bar, n, "bar") == DF_OK);
    assert(df_col_append(df, baz, n, "baz") == DF_OK);

    return df;
}

void test_df_col_arithmetic(
    double *(*df_func)(const dataframe_t *, const char *, const char *, int *), 
    double (*func)(double, double)
) {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double *data = df_func(df, "foo", "bar", &err);
    assert(err == DF_OK);

    double *foo = df_col_get(df, "foo", &err);
    assert(err == DF_OK);

    double *bar = df_col_get(df, "bar", &err);
    assert(err == DF_OK);

    assert(data != NULL);
    for (size_t r = 0; r < df->n_rows; r++)
        assert(data[r] == func(foo[r], bar[r]));

    // error case
    assert(df_func(df, "foo", "qux", &err) == NULL);
    assert(err == DF_NO_COL);

    assert(df_func(df, "qux", "foo", &err) == NULL);
    assert(err == DF_NO_COL);

    assert(df_func(df, "qux", "qux", &err) == NULL);
    assert(err == DF_NO_COL);

    free(bar);
    free(foo);
    free(data);
    df_free(df);
}

void test_df_col_arithmetic_s(
    double *(*df_func)(const dataframe_t *, const char *, const double, int *), 
    double (*func)(double, double)
) {
    const double SCALAR = 9;

    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double *data = df_func(df, "foo", SCALAR, &err);
    assert(err == DF_OK);

    double *foo = df_col_get(df, "foo", &err);
    assert(err == DF_OK);

    assert(data != NULL);
    for (size_t r = 0; r < df->n_rows; r++)
        assert(data[r] == func(foo[r], SCALAR));

    // error case
    assert(df_func(df, "qux", SCALAR, &err) == NULL);
    assert(err == DF_NO_COL);

    free(foo);
    free(data);
    df_free(df);
}

void test_df_col_sum() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_sum(df, "foo", &err);
    assert(err == DF_OK);

    double sum = 0;
    for (size_t i = 0; i < df->n_rows; i++)
        sum += df->data[i * df->n_cols];

    assert(fabs(data - sum) < 1e-6);

    // error case
    assert(isnan(df_col_sum(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}

void test_df_col_mean() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_mean(df, "foo", &err);
    assert(err == DF_OK);

    double mean = 0;
    for (size_t i = 0; i < df->n_rows; i++)
        mean += df->data[i * df->n_cols];
    mean /= df->n_rows;

    assert(fabs(data - mean) < 1e-6);

    // error case
    assert(isnan(df_col_mean(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}

void test_df_col_min() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_min(df, "foo", &err);
    assert(err == DF_OK);

    double min = df->data[0];
    for (size_t i = 1; i < df->n_rows; i++)
        if (min > df->data[i * df->n_cols])
            min = df->data[i * df->n_cols];

    assert(min == data);

    // error case
    assert(isnan(df_col_min(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}

void test_df_col_max() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_max(df, "foo", &err);
    assert(err == DF_OK);

    double max = df->data[0];
    for (size_t i = 1; i < df->n_rows; i++)
        if (max < df->data[i * df->n_cols])
            max = df->data[i * df->n_cols];

    assert(max == data);

    // error case
    assert(isnan(df_col_max(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}

void test_df_col_var() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_var(df, "foo", &err);
    assert(err == DF_OK);

    double mean = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        mean += df->data[r * df->n_cols];
    mean /= df->n_rows;

    double var = 0;
    for (size_t i = 0; i < df->n_rows; i++)
        var += pow(df->data[i * df->n_cols] - mean, 2);
    var /= df->n_rows;

    assert(var == data);

    // error case
    assert(isnan(df_col_var(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}

void test_df_col_std() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double data = df_col_std(df, "foo", &err);
    assert(err == DF_OK);

    double mean = 0;
    for (size_t r = 0; r < df->n_rows; r++)
        mean += df->data[r * df->n_cols];
    mean /= df->n_rows;

    double var = 0;
    for (size_t i = 0; i < df->n_rows; i++)
        var += pow(df->data[i * df->n_cols] - mean, 2);
    var /= df->n_rows;

    double std = sqrt(var);
    assert(std == data);

    // error case
    assert(isnan(df_col_std(df, "qux", &err)));
    assert(err == DF_NO_COL);

    df_free(df);
}
