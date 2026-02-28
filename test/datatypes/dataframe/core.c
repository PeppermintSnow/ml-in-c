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

    dataframe_t *df = df_from_array(foo, n, "foo");
    df_col_append(df, bar, n, "bar");
    df_col_append(df, baz, n, "baz");

    return df;
}

void test_df_from_array() {
    // Base case
    double *data = generate_dummy_data(SIZE);
    dataframe_t *df = df_from_array(data, SIZE, "foo");

    assert(df != NULL);
    assert(df->n_cols == 1);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);

    df_free(df);

    // Error cases
    assert(df_from_array(NULL, 0, NULL) == NULL);
    assert(df_from_array(data, 0, "bar") == NULL);
    assert(df_from_array(data, SIZE, NULL) == NULL);

    free(data);
}

void test_df_col_get() {
    // Base case
    dataframe_t *df = generate_dummy_df(SIZE);
    double *col_data = df_col_get(df, "bar");
    
    assert(col_data != NULL);
    for (size_t i = 0; i < df->n_rows; i++)
        assert(col_data[i] == df->data[i * df->n_cols + 1]);

    // Error cases
    assert(df_col_get(df, "bax") == NULL);

    free(col_data);
    df_free(df);
}

void test_df_col_append() {
    // Base case
    double *data = generate_dummy_data(SIZE);
    dataframe_t *df = df_from_array(data, SIZE, "foo");

    df_col_append(df, data, SIZE, "bar");
    df_col_append(df, data, SIZE, "baz");

    assert(df != NULL);
    assert(df->n_cols == 3);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);
    assert(strcmp(df->columns[1], "bar") == 0);
    assert(strcmp(df->columns[2], "baz") == 0);

    // Error cases
    assert(df_col_append(df, data, SIZE, "foo") == DF_ERR_DUPLICATE_COLUMN);
    assert(df_col_append(df, data, SIZE - 1, "bax") == DF_ERR_ROW_MISMATCH);

    df_free(df);
    free(data);
}

void test_df_col_drop() {
    // Base case
    dataframe_t *df = generate_dummy_df(SIZE);

    df_col_drop(df, "foo");

    assert(df != NULL);
    assert(df->n_cols == 2);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "bar") == 0);
    assert(strcmp(df->columns[1], "baz") == 0);

    // Error cases
    df_col_drop(df, "bar");

    assert(df_col_drop(df, "foo") == DF_ERR_NONEXISTENT_COLUMN);
    assert(df_col_drop(df, "baz") == DF_ERR_LAST_COLUMN);

    df_free(df);
}

void test_df_row_get() {
    // Base case
    const size_t INDEX = 3;
    dataframe_t *df = generate_dummy_df(5);
    double *row_data = df_row_get(df, INDEX);

    assert(row_data != NULL);
    for (size_t i = 0; i < df->n_cols; i++)
        assert(row_data[i] == df->data[INDEX * df->n_cols + i]);

    // Error case
    assert(df_row_get(df, 99) == NULL);

    free(row_data);
    df_free(df);

}

void test_df_row_append() {
    // Base case
    double data[] = {1, 2, 3};
    dataframe_t *df = generate_dummy_df(SIZE);

    df_row_append(df, data, LEN(data));
    df_row_append(df, data, LEN(data));

    assert(df != NULL);
    assert(df->n_rows == SIZE + 2);

    // Error cases
    assert(df_row_append(df, data, LEN(data) + 1) == DF_ERR_COLUMN_MISMATCH);

    df_free(df);
}

void test_df_row_drop() {
    // Base case
    dataframe_t *df = generate_dummy_df(SIZE);

    for (size_t i = 0; i < 25; i++)
        df_row_drop(df, i);

    assert(df != NULL);
    assert(df->n_rows == SIZE - 25);

    // Error cases
    assert(df_row_drop(df, SIZE) == DF_ERR_NONEXISTENT_ROW);

    df_free(df);
    df = generate_dummy_df(1);
    assert(df_row_drop(df, 0) == DF_ERR_LAST_ROW);
    df_free(df);
}
