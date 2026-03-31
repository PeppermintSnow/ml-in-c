#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "dtypes/col/core/type.h"
#include "dtypes/col/core/lifecycle.h"
#include "dtypes/col/core/accessors.h"
#include "test_utils/col.h"

void test_col_at();
void test_col_get();

static const size_t SIZE = 999;
static const size_t S_IDX = 0;
static const size_t M_IDX = SIZE / 2;
static const size_t E_IDX = SIZE - 1;

int main() {
    test_col_at();
    test_col_get();
}

void test_col_at() {
    int err;

    /* valid */
    double *double_data = col_double_data_create(SIZE);
    struct col *col_double = col_double_dummy_create("double", SIZE);
    const double *double_start = col_double_at(col_double, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const double *double_middle = col_double_at(col_double, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const double *double_end = col_double_at(col_double, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(fabs(*double_start - double_data[S_IDX]) < 1e-12f);
    assert(fabs(*double_middle - double_data[M_IDX]) < 1e-12f);
    assert(fabs(*double_end - double_data[E_IDX]) < 1e-12f);
    col_free(col_double);
    free(double_data);

    float *float_data = col_float_data_create(SIZE);
    struct col *col_float = col_float_dummy_create("float", SIZE);
    const float *float_start = col_float_at(col_float, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const float *float_middle = col_float_at(col_float, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const float *float_end = col_float_at(col_float, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(fabs(*float_start - float_data[S_IDX]) < 1e-6f);
    assert(fabs(*float_middle - float_data[M_IDX]) < 1e-6f);
    assert(fabs(*float_end - float_data[E_IDX]) < 1e-6f);
    col_free(col_float);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(SIZE);
    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    const int64_t *int64_start = col_int64_at(col_int64, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const int64_t *int64_middle = col_int64_at(col_int64, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const int64_t *int64_end = col_int64_at(col_int64, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(*int64_start == int64_data[S_IDX]);
    assert(*int64_middle == int64_data[M_IDX]);
    assert(*int64_end == int64_data[E_IDX]);
    col_free(col_int64);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(SIZE);
    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    const int32_t *int32_start = col_int32_at(col_int32, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const int32_t *int32_middle = col_int32_at(col_int32, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const int32_t *int32_end = col_int32_at(col_int32, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(*int32_start == int32_data[S_IDX]);
    assert(*int32_middle == int32_data[M_IDX]);
    assert(*int32_end == int32_data[E_IDX]);
    col_free(col_int32);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(SIZE);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    const uint8_t *uint8_start = col_uint8_at(col_uint8, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const uint8_t *uint8_middle = col_uint8_at(col_uint8, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const uint8_t *uint8_end = col_uint8_at(col_uint8, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(*uint8_start == uint8_data[S_IDX]);
    assert(*uint8_middle == uint8_data[M_IDX]);
    assert(*uint8_end == uint8_data[E_IDX]);
    col_free(col_uint8);
    free(uint8_data);

    char **string_data = col_string_data_create(SIZE);
    struct col *col_string = col_string_dummy_create("string", SIZE);
    const char *string_start = col_string_at(col_string, S_IDX, &err);
    assert(err == COL_ERR_OK);
    const char *string_middle = col_string_at(col_string, M_IDX, &err);
    assert(err == COL_ERR_OK);
    const char *string_end = col_string_at(col_string, E_IDX, &err);
    assert(err == COL_ERR_OK);
    assert(strcmp(string_start, string_data[S_IDX]) == 0);
    assert(strcmp(string_middle, string_data[M_IDX]) == 0);
    assert(strcmp(string_end, string_data[E_IDX]) == 0);
    col_free(col_string);
    for (size_t i = 0; i < 999; i++)
        free(string_data[i]);
    free(string_data);

    /* err */
    struct col *col_valid = col_double_dummy_create("valid", 999);

    assert(col_double_at(col_valid, col_valid->n_rows + 999, &err) == NULL);
    assert(err == COL_ERR_OUT_OF_BOUNDS);

    assert(col_float_at(col_valid, 0, &err) == NULL);
    assert(err == COL_ERR_INVALID_DTYPE);

    col_free(col_valid);
}

void test_col_get() {
    int err;

    /* valid */
    double *double_data = col_double_data_create(SIZE);
    struct col *col_double = col_double_dummy_create("double", SIZE);
    const double *col_double_data = col_double_get(col_double, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(fabs(col_double_data[i] - double_data[i]) < 1e-12f);
    col_free(col_double);
    free(double_data);

    float *float_data = col_float_data_create(SIZE);
    struct col *col_float = col_float_dummy_create("float", SIZE);
    const float *col_float_data = col_float_get(col_float, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(fabsf(col_float_data[i] - float_data[i]) < 1e-6f);
    col_free(col_float);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(SIZE);
    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    const int64_t *col_int64_data = col_int64_get(col_int64, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(col_int64_data[i] == int64_data[i]);
    col_free(col_int64);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(SIZE);
    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    const int32_t *col_int32_data = col_int32_get(col_int32, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(col_int32_data[i] == int32_data[i]);
    col_free(col_int32);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(SIZE);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    const uint8_t *col_uint8_data = col_uint8_get(col_uint8, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(col_uint8_data[i] == uint8_data[i]);
    col_free(col_uint8);
    free(uint8_data);

    char **string_data = col_string_data_create(SIZE);
    struct col *col_string = col_string_dummy_create("string", SIZE);
    const char **col_string_data = col_string_get(col_string, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < SIZE; i++)
        assert(strcmp(col_string_data[i], string_data[i]) == 0);
    col_free(col_string);
    for (size_t i = 0; i < SIZE; i++)
        free(string_data[i]);
    free(string_data);

    /* err */
    struct col *col_valid = col_double_dummy_create("valid", 999);

    assert(col_float_get(col_valid, &err) == NULL);
    assert(err == COL_ERR_INVALID_DTYPE);

    col_free(col_valid);
}
