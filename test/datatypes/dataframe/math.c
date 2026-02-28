#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/math.h"
#include <assert.h>
#include <stdlib.h>

#define SIZE 1000

dataframe_t *generate_dummy_df(size_t n);

void test_df_col_arithmetic(
    double *(*df_func)(dataframe_t *, const char *, const char *), 
    double (*func)(double, double)
);

void test_df_col_arithmetic_s(
    double *(*df_func)(dataframe_t *, const char *, const double), 
    double (*func)(double, double)
);

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

void test_df_col_arithmetic(
    double *(*df_func)(dataframe_t *, const char *, const char *), 
    double (*func)(double, double)
) {
    // base case
    dataframe_t *df = generate_dummy_df(SIZE);
    double *data = df_func(df, "foo", "bar");
    double *foo = df_col_get(df, "foo");
    double *bar = df_col_get(df, "bar");

    assert(data != NULL);
    for (size_t r = 0; r < df->n_rows; r++)
        assert(data[r] == func(foo[r], bar[r]));

    // error case
    assert(df_func(df, "foo", "qux") == NULL);
    assert(df_func(df, "qux", "foo") == NULL);
    assert(df_func(df, "qux", "qux") == NULL);

    free(bar);
    free(foo);
    free(data);
    df_free(df);
}

void test_df_col_arithmetic_s(
    double *(*df_func)(dataframe_t *, const char *, const double), 
    double (*func)(double, double)
) {
    const double SCALAR = 9;

    // base case
    dataframe_t *df = generate_dummy_df(SIZE);
    double *data = df_func(df, "foo", SCALAR);
    double *foo = df_col_get(df, "foo");

    assert(data != NULL);
    for (size_t r = 0; r < df->n_rows; r++)
        assert(data[r] == func(foo[r], SCALAR));

    // error case
    assert(df_func(df, "qux", SCALAR) == NULL);

    free(foo);
    free(data);
    df_free(df);
}
