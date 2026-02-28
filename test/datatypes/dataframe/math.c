#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <assert.h>
#include <stdlib.h>

#define SIZE 1000

dataframe_t *generate_dummy_df(size_t n);

void test_df_col_add();

int main() {
    test_df_col_add();
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

void test_df_col_add() {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);
    double *data = df_col_add(df, "foo", "bar");
    double *foo = df_col_get(df, "foo");
    double *bar = df_col_get(df, "bar");

    assert(data != NULL);
    for (size_t r = 0; r < df->n_rows; r++)
        assert(data[r] == foo[r] + bar[r]);

    // error case
    assert(df_col_add(df, "foo", "qux") == NULL);
    assert(df_col_add(df, "qux", "foo") == NULL);
    assert(df_col_add(df, "qux", "qux") == NULL);

    free(data);
    free(bar);
    free(foo);
    df_free(df);
}
