#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH "dataframe_io_test.csv"
#define SIZE 1000

int main() {
    // base case
    double foo[SIZE], bar[SIZE], baz[SIZE], qux[SIZE];
    for (size_t i = 0; i < SIZE; i++) {
        foo[i] = i;
        bar[i] = i * 2;
        baz[i] = i * 3;
        qux[i] = i * 4;
    }

    int err;
    dataframe_t *df = df_from_array(foo, SIZE, "foo", &err);
    assert(err == DF_OK);

	assert(df_col_append(df, bar, SIZE, "bar") == DF_OK);
	assert(df_col_append(df, baz, SIZE, "baz") == DF_OK);
	assert(df_col_append(df, qux, SIZE, "qux") == DF_OK);

    assert(df != NULL);
    assert(df->n_cols == 4);
    assert(df->n_rows == SIZE);

    assert(df_write_csv(df, FILEPATH, 0) == DF_OK);

    dataframe_t *csv_df = df_read_csv(FILEPATH, &err);
    assert(err == DF_OK);
    
    assert(csv_df != NULL);
    assert(df->n_rows == csv_df->n_rows);
    assert(df->n_cols == csv_df->n_cols);
    for (size_t c = 0; c < df->n_cols; c++) {
        assert(strcmp(df->columns[c], csv_df->columns[c]) == 0);
        for (size_t r = 0; r < df->n_rows; r++) {
            assert(df->data[r * df->n_cols + c] == csv_df->data[r * csv_df->n_cols + c]);
        }
    }

    df_free(df);
    df_free(csv_df);

    // error case
    FILE *mismatch_fptr = fopen("col_mismatch.csv", "w");
    fputs("foo,bar,baz\n1,2,3\n4,5\n,7,8,9", mismatch_fptr);
    fclose(mismatch_fptr);

    FILE *invalid_fptr = fopen("invalid_char.csv", "w");
    fputs("foo,bar,baz\n1,2,3\n4,5,invalid\n,7,8,9", invalid_fptr);
    fclose(invalid_fptr);

    assert(df_read_csv("col_mismatch.csv", &err) == NULL);
    assert(err == DF_IO);

    assert(df_read_csv("invalid_char.csv", &err) == NULL);
    assert(err == DF_IO);

    assert(df_read_csv("non_existent_file.csv", &err) == NULL);
    assert(err == DF_IO);

    // cleanup
    remove(FILEPATH);
    remove("col_mismatch.csv");
    remove("invalid_char.csv");
}
