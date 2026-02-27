#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include "..\\..\\..\\include\\datatypes\\dataframe\\core.h"
#else
    #include "../../../include/datatypes/dataframe/core.h"
#endif

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define SIZE 1000

double *generate_dummy_data(size_t n);
dataframe_t *generate_dummy_df(size_t n);

void test_df_create_from_array();
void test_df_column_add();
void test_df_column_delete();
void test_df_row_get();
void test_df_row_add();
void test_df_row_delete();

int main() {
    test_df_create_from_array();
    test_df_column_add();
    test_df_column_delete();
    test_df_row_get();
    test_df_row_add();
    test_df_row_delete();
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
    double data[n];
    for (size_t i = 0; i < n; i++)
        data[i] = i;

    dataframe_t *df = df_create_from_array(data, n, "foo");
    df_column_add(df, data, n, "bar");
    df_column_add(df, data, n, "baz");

    return df;
}

void test_df_create_from_array() {
    // Base case
    double *data = generate_dummy_data(SIZE);
    dataframe_t *df = df_create_from_array(data, SIZE, "foo");

    assert(df != NULL);
    assert(df->n_columns == 1);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);

    df_free(df);

    // Error cases
    assert(df_create_from_array(NULL, 0, NULL) == NULL);
    assert(df_create_from_array(data, 0, "bar") == NULL);
    assert(df_create_from_array(data, SIZE, NULL) == NULL);

    free(data);
}

void test_df_column_add() {
    // Base case
    double *data = generate_dummy_data(SIZE);
    dataframe_t *df = df_create_from_array(data, SIZE, "foo");

    df_column_add(df, data, SIZE, "bar");
    df_column_add(df, data, SIZE, "baz");

    assert(df != NULL);
    assert(df->n_columns == 3);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "foo") == 0);
    assert(strcmp(df->columns[1], "bar") == 0);
    assert(strcmp(df->columns[2], "baz") == 0);

    // Error cases
    assert(df_column_add(df, data, SIZE, "foo") == DF_ERR_DUPLICATE_COLUMN);
    assert(df_column_add(df, data, SIZE - 1, "bax") == DF_ERR_ROW_MISMATCH);

    df_free(df);
    free(data);
}

void test_df_column_delete() {
    // Base case
    dataframe_t *df = generate_dummy_df(SIZE);

    df_column_delete(df, "foo");

    assert(df != NULL);
    assert(df->n_columns == 2);
    assert(df->n_rows == SIZE);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "bar") == 0);
    assert(strcmp(df->columns[1], "baz") == 0);

    // Error cases
    df_column_delete(df, "bar");

    assert(df_column_delete(df, "foo") == DF_ERR_NONEXISTENT_COLUMN);
    assert(df_column_delete(df, "baz") == DF_ERR_LAST_COLUMN);

    df_free(df);
}

void test_df_row_get() {
    // Base case
    const size_t INDEX = 3;
    dataframe_t *df = generate_dummy_df(5);
    dataframe_t *row3_df = df_row_get(df, INDEX);

    assert(row3_df != NULL);
    assert(row3_df->n_rows == 1);
    assert(row3_df->n_columns == df->n_columns);
    for (size_t i = 0; i < df->n_columns; i++) {
        assert(strcmp(row3_df->columns[i], df->columns[i]) == 0);
        assert(row3_df->data[i] == df->data[INDEX * df->n_columns + i]);
    }

    // Error case
    assert(df_row_get(df, 99) == NULL);

    df_free(row3_df);
    df_free(df);

}

void test_df_row_add() {
    // Base case
    double data[] = {1, 2, 3};
    dataframe_t *df = generate_dummy_df(SIZE);

    df_row_add(df, data, LEN(data));
    df_row_add(df, data, LEN(data));

    assert(df != NULL);
    assert(df->n_rows == SIZE + 2);

    // Error cases
    assert(df_row_add(df, data, LEN(data) + 1) == DF_ERR_COLUMN_MISMATCH);

    df_free(df);
}

void test_df_row_delete() {
    // Base case
    dataframe_t *df = generate_dummy_df(SIZE);

    for (size_t i = 0; i < 25; i++)
        df_row_delete(df, i);

    assert(df != NULL);
    assert(df->n_rows == SIZE - 25);

    // Error cases
    assert(df_row_delete(df, SIZE) == DF_ERR_NONEXISTENT_ROW);

    df_free(df);
    df = generate_dummy_df(1);
    assert(df_row_delete(df, 0) == DF_ERR_LAST_ROW);
    df_free(df);
}
