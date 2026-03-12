#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/ops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_df_clone();
void test_df_mask();
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
    test_df_clone();
    test_df_mask();
    test_df_col_select();
    test_df_row_select();
}

void test_df_clone() {
    int err;

    dataframe_t *df = generate_dummy_df(1000);
    dataframe_t *clone_df = df_clone(df, &err);
    assert(err == DF_OK);

    assert(df->n_rows == clone_df->n_rows);
    assert(df->n_cols == clone_df->n_cols);
    for (size_t r = 0; r < df->n_rows; r++)
        for (size_t c = 0; c < df->n_cols; c++) {
            size_t idx = r * df->n_cols + c;
            assert(df->data[idx] == clone_df->data[idx]); 
        }

    for (size_t i = 0; i < df->n_cols; i++)
        assert(strcmp(df->columns[i], clone_df->columns[i]) == 0);

    df_free(clone_df);
    df_free(df);
}

void test_df_mask() {
    int err;

    dataframe_t *df = generate_dummy_df(1000);
    dataframe_t *clone_df = df_clone(df, &err);
    assert(err == DF_OK);

    df_mask_t *mask = df_mask_create(df->n_rows, &err);
    assert(err == DF_OK);

    assert(mask->n_rows == df->n_rows);
    assert(mask->n_keep == df->n_rows);

    // 500 <= foo <= 550
    assert(df_mask_and(mask, df, "foo", DF_MASK_GE, 500) == DF_OK);
    assert(mask->n_keep == 500);
    assert(df_mask_and(mask, df, "foo", DF_MASK_LE, 550) == DF_OK);
    assert(mask->n_keep == 51); // 51 integers in 550 - 550

    // 1849 < bar < 1901
    assert(df_mask_or(mask, df, "bar", DF_MASK_GT, 1849) == DF_OK);
    assert(mask->n_keep == 126); // (51 + 75) mod 2 integers in 1849 - 1999
    assert(df_mask_and(mask, df, "bar", DF_MASK_LT, 1901) == DF_OK);
    assert(mask->n_keep == 77); // (51 + 26) mod 2 integers in 1849 - 1901

    // baz == 2994; baz == 2997
    assert(df_mask_or(mask, df, "baz", DF_MASK_EQ, 2994) == DF_OK);
    assert(mask->n_keep == 78);
    assert(df_mask_or(mask, df, "baz", DF_MASK_EQ, 2997) == DF_OK);
    assert(mask->n_keep == 79);

    // baz != 2994
    assert(df_mask_and(mask, df, "baz", DF_MASK_NE, 2994) == DF_OK);
    assert(mask->n_keep == 78);

    assert(df_mask_apply(df, mask) == DF_OK);

    assert(df->n_rows == mask->n_keep);
    for (size_t r = 0; r < df->n_rows; r++) {
        double *row = df_row_get(df, r, &err);
        if (r < 51) { // first 51 rows contain 500 <= foo <= 550
            assert(row[0] == 500 + r);
            assert(row[1] == (500 + r) * 2);
            assert(row[2] == (500 + r) * 3);
        } else if (r < 77) { // rows 51 - 77 contain 1849 < bar < 1901
            assert(row[0] == 925 + (r - 51));
            assert(row[1] == 1850 + ((r - 51) * 2));
            assert(row[2] == 2775 + ((r - 51) * 3));
        } else { // row 78 contains bar == 2997
            assert(row[0] == 999);
            assert(row[1] == 1998);
            assert(row[2] == 2997);
        }
        free(row);
    }

    // error case
    assert(df_mask_or(mask, df, "qux", DF_MASK_EQ, 0) == DF_NO_COL);
    assert(df_mask_or(mask, df, "foo", DF_MASK_EQ, 0) == DF_ROW_MISMATCH);
    assert(df_mask_and(mask, df, "foo", DF_MASK_EQ, 0) == DF_ROW_MISMATCH);
    assert(df_mask_apply(df, mask) == DF_ROW_MISMATCH);

    df_mask_free(mask);
    df_free(clone_df);
    df_free(df);
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
