#include "../../../include/datatypes/dataframe/core.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define SIZE 1000

double *generate_dummy_data(size_t n);
dataframe_t *generate_dummy_df(size_t n);

void test_df_from_array();
void test_df_col_get();
void test_df_col_append();
void test_df_col_drop();
void test_df_row_get();
void test_df_row_append();
void test_df_row_drop();

int main() {
    test_df_from_array();
    test_df_col_get();
    test_df_col_append();
    test_df_col_drop();
    test_df_row_get();
    test_df_row_append();
    test_df_row_drop();
}

double *generate_dummy_data(size_t n) {
    double *data = malloc(n * sizeof(double));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i;

    return data;
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

void test_df_from_array() {
    // base case
    double *data = generate_dummy_data(SIZE);

    int err;
    dataframe_t *df = df_from_array(data, SIZE, "foo", &err);
    assert(err == DF_OK);

    assert(df != NULL);
    assert(df->n_cols == 1);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);

    df_free(df);

    // error cases
    assert(df_from_array(NULL, 0, NULL, &err) == NULL);
    assert(err == DF_BAD_ARG);

    assert(df_from_array(data, 0, "bar", &err) == NULL);
    assert(err == DF_BAD_ARG);

    assert(df_from_array(data, SIZE, NULL, &err) == NULL);
    assert(err == DF_BAD_ARG);

    free(data);
}

void test_df_col_get() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    int err;
    double *col_data = df_col_get(df, "bar", &err);
    assert(err == DF_OK);
    
    assert(col_data != NULL);
    for (size_t i = 0; i < df->n_rows; i++)
        assert(col_data[i] == df->data[i * df->n_cols + 1]);

    // error cases
    assert(df_col_get(df, "qux", &err) == NULL);
    assert(err == DF_NO_COL);

    free(col_data);
    df_free(df);
}

void test_df_col_append() {
    // base case
    double *data = generate_dummy_data(SIZE);
    
    int err;
    dataframe_t *df = df_from_array(data, SIZE, "foo", &err);
    assert(err == DF_OK);

    assert(df_col_append(df, data, SIZE, "bar") == DF_OK);
    assert(df_col_append(df, data, SIZE, "baz") == DF_OK);

    assert(df != NULL);
    assert(df->n_cols == 3);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);
    assert(strcmp(df->columns[1], "bar") == 0);
    assert(strcmp(df->columns[2], "baz") == 0);

    // error cases
    assert(df_col_append(df, data, SIZE, "foo") == DF_COL_EXISTS);
    assert(df_col_append(df, data, SIZE - 1, "bax") == DF_ROW_MISMATCH);

    df_free(df);
    free(data);
}

void test_df_col_drop() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    assert(df_col_drop(df, "foo") == DF_OK);

    assert(df != NULL);
    assert(df->n_cols == 2);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "bar") == 0);
    assert(strcmp(df->columns[1], "baz") == 0);

    assert(df_col_drop(df, "bar") == DF_OK);

    // error cases
    assert(df_col_drop(df, "foo") == DF_NO_COL);
    assert(df_col_drop(df, "baz") == DF_LAST_COL);

    df_free(df);
}

void test_df_row_get() {
    // base case
    const size_t INDEX = 3;
    dataframe_t *df = generate_dummy_df(5);

    int err;
    double *row_data = df_row_get(df, INDEX, &err);
    assert(err == DF_OK);

    assert(row_data != NULL);
    for (size_t i = 0; i < df->n_cols; i++)
        assert(row_data[i] == df->data[INDEX * df->n_cols + i]);

    // error case
    assert(df_row_get(df, 99, &err) == NULL);
    assert(err == DF_NO_ROW);

    free(row_data);
    df_free(df);
}

void test_df_row_append() {
    // base case
    double data[] = {1, 2, 3};
    dataframe_t *df = generate_dummy_df(SIZE);

    assert(df_row_append(df, data, LEN(data)) == DF_OK);
    assert(df_row_append(df, data, LEN(data)) == DF_OK);

    assert(df != NULL);
    assert(df->n_rows == SIZE + 2);

    // error cases
    assert(df_row_append(df, data, LEN(data) + 1) == DF_COL_MISMATCH);

    df_free(df);
}

void test_df_row_drop() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);

    for (size_t i = 0; i < 25; i++)
        assert(df_row_drop(df, i) == DF_OK);

    assert(df != NULL);
    assert(df->n_rows == SIZE - 25);

    // error cases
    assert(df_row_drop(df, SIZE) == DF_NO_ROW);

    df_free(df);

    df = generate_dummy_df(1);
    assert(df_row_drop(df, 0) == DF_LAST_ROW);
    df_free(df);
}
