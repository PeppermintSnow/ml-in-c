#include <assert.h>
#include <stdlib.h>
#include "datatypes/dataframe/ops/select.h"

void test_df_col_select();
void test_df_row_select();

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

int main() {
    test_df_col_select();
    test_df_row_select();
}


void test_df_col_select() {
    int err;

    dataframe_t *df = generate_dummy_df(1000);
    dataframe_t *clone_df = df_clone(df, &err);
    assert(err == DF_OK);

    const char *cols[] = { "foo", "baz" };
    size_t len = sizeof(cols) / sizeof(cols[0]);

    assert(df_col_select(df, cols, len) == DF_OK);
    assert(df->n_cols == len);

    double *foo = df_col_get(df, "foo", &err);
    assert(err == DF_OK);
    double *baz = df_col_get(df, "baz", &err);
    assert(err == DF_OK);

    double *clone_foo = df_col_get(clone_df, "foo", &err);
    assert(err == DF_OK);
    double *clone_baz = df_col_get(clone_df, "baz", &err);
    assert(err == DF_OK);

    for (size_t r = 0; r < df->n_rows; r++) {
        assert(foo[r] == clone_foo[r]);
        assert(baz[r] == clone_baz[r]);
    }

    // error case
    const char *invalid[] = { "foo", "qux" };
    size_t invalid_len = sizeof(invalid) / sizeof(invalid[0]);

    assert(df_col_select(clone_df, invalid, invalid_len) == DF_NO_COL);

    free(clone_baz);
    free(clone_foo);
    free(baz);
    free(foo);
    df_free(clone_df);
    df_free(df);
}

void test_df_row_select() {
    int err;

    dataframe_t *df = generate_dummy_df(1000);
    dataframe_t *clone_df = df_clone(df, &err);
    assert(err == DF_OK);

    assert(df_row_select(df, 500, 1000) == DF_OK);
    assert(df->n_rows == 500);

    for (size_t r = 0; r < df->n_rows; r++)
        for (size_t c = 0; c < df->n_cols; c++)
            assert(
                df->data[r * df->n_cols + c] 
                    == clone_df->data[(r + 500) * df->n_cols + c]
            );

    // error case
    assert(df_row_select(df, 1000, 500) == DF_BAD_ARG);
    assert(df_row_select(df, 500, 1001) == DF_NO_ROW);
    assert(df_row_select(df, 1001, 9999) == DF_NO_ROW);

    df_free(clone_df);
    df_free(df);
}
