#include <assert.h>
#include <string.h>

#ifdef _WIN32
    #include "..\\..\\..\\include\\datatypes\\dataframe\\core.h"
#else
    #include "../../../include/datatypes/dataframe/core.h"
#endif

dataframe_t *create_dummy_df();

void test_df_create_from_array();
void test_df_column_add();
void test_df_column_delete();
void test_df_row_add();
void test_df_row_delete();

int main() {
    test_df_create_from_array();
    test_df_column_add();
    test_df_column_delete();
    test_df_row_add();
    test_df_row_delete();
}

dataframe_t *create_dummy_df() {
    double data[100000];
    for (int i = 0; i < 100000; i++)
        data[i] = i * 2;

    size_t len = sizeof(data) / sizeof(data[0]);

    return df_create_from_array(data, len, "column0");
}

void test_df_create_from_array() {
    // Base case
    dataframe_t *df = create_dummy_df();

    assert(df != NULL);
    assert(df->n_columns == 1);
    assert(df->n_rows == 100000);
    assert(df->columns != NULL);
    assert(strcmp(df->columns[0], "column0") == 0);

    df_free(df);

    // Error cases
    dataframe_t *error_df = df_create_from_array(NULL)
}

