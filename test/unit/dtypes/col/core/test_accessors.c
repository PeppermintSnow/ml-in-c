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

int main() {
    test_col_at();
    test_col_get();
}

void test_col_at() {
    int err;
    size_t size = 999;
    size_t s_idx = 0;
    size_t m_idx = size / 2;
    size_t e_idx = size - 1;

    /* valid */
    double *double_data = col_double_data_create(size);
    struct col *col_double = col_double_dummy_create("double", size);
    const double *double_start = col_double_at(col_double, s_idx, &err);
    assert(err == COL_ERR_OK);
    const double *double_middle = col_double_at(col_double, m_idx, &err);
    assert(err == COL_ERR_OK);
    const double *double_end = col_double_at(col_double, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(fabs(*double_start - double_data[s_idx]) < 1e-12f);
    assert(fabs(*double_middle - double_data[m_idx]) < 1e-12f);
    assert(fabs(*double_end - double_data[e_idx]) < 1e-12f);
    col_free(col_double);
    free(double_data);

    float *float_data = col_float_data_create(size);
    struct col *col_float = col_float_dummy_create("float", size);
    const float *float_start = col_float_at(col_float, s_idx, &err);
    assert(err == COL_ERR_OK);
    const float *float_middle = col_float_at(col_float, m_idx, &err);
    assert(err == COL_ERR_OK);
    const float *float_end = col_float_at(col_float, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(fabs(*float_start - float_data[s_idx]) < 1e-6f);
    assert(fabs(*float_middle - float_data[m_idx]) < 1e-6f);
    assert(fabs(*float_end - float_data[e_idx]) < 1e-6f);
    col_free(col_float);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(size);
    struct col *col_int64 = col_int64_dummy_create("int64", size);
    const int64_t *int64_start = col_int64_at(col_int64, s_idx, &err);
    assert(err == COL_ERR_OK);
    const int64_t *int64_middle = col_int64_at(col_int64, m_idx, &err);
    assert(err == COL_ERR_OK);
    const int64_t *int64_end = col_int64_at(col_int64, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(*int64_start == int64_data[s_idx]);
    assert(*int64_middle == int64_data[m_idx]);
    assert(*int64_end == int64_data[e_idx]);
    col_free(col_int64);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(size);
    struct col *col_int32 = col_int32_dummy_create("int32", size);
    const int32_t *int32_start = col_int32_at(col_int32, s_idx, &err);
    assert(err == COL_ERR_OK);
    const int32_t *int32_middle = col_int32_at(col_int32, m_idx, &err);
    assert(err == COL_ERR_OK);
    const int32_t *int32_end = col_int32_at(col_int32, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(*int32_start == int32_data[s_idx]);
    assert(*int32_middle == int32_data[m_idx]);
    assert(*int32_end == int32_data[e_idx]);
    col_free(col_int32);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(size);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", size);
    const uint8_t *uint8_start = col_uint8_at(col_uint8, s_idx, &err);
    assert(err == COL_ERR_OK);
    const uint8_t *uint8_middle = col_uint8_at(col_uint8, m_idx, &err);
    assert(err == COL_ERR_OK);
    const uint8_t *uint8_end = col_uint8_at(col_uint8, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(*uint8_start == uint8_data[s_idx]);
    assert(*uint8_middle == uint8_data[m_idx]);
    assert(*uint8_end == uint8_data[e_idx]);
    col_free(col_uint8);
    free(uint8_data);

    char **string_data = col_string_data_create(size);
    struct col *col_string = col_string_dummy_create("string", size);
    const char *string_start = col_string_at(col_string, s_idx, &err);
    assert(err == COL_ERR_OK);
    const char *string_middle = col_string_at(col_string, m_idx, &err);
    assert(err == COL_ERR_OK);
    const char *string_end = col_string_at(col_string, e_idx, &err);
    assert(err == COL_ERR_OK);
    assert(strcmp(string_start, string_data[s_idx]) == 0);
    assert(strcmp(string_middle, string_data[m_idx]) == 0);
    assert(strcmp(string_end, string_data[e_idx]) == 0);
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
    size_t size = 999;

    /* valid */
    double *double_data = col_double_data_create(size);
    struct col *col_double = col_double_dummy_create("double", size);
    const double *col_double_data = col_double_get(col_double, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(fabs(col_double_data[i] - double_data[i]) < 1e-12f);
    col_free(col_double);
    free(double_data);

    float *float_data = col_float_data_create(size);
    struct col *col_float = col_float_dummy_create("float", size);
    const float *col_float_data = col_float_get(col_float, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(fabsf(col_float_data[i] - float_data[i]) < 1e-6f);
    col_free(col_float);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(size);
    struct col *col_int64 = col_int64_dummy_create("int64", size);
    const int64_t *col_int64_data = col_int64_get(col_int64, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(col_int64_data[i] == int64_data[i]);
    col_free(col_int64);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(size);
    struct col *col_int32 = col_int32_dummy_create("int32", size);
    const int32_t *col_int32_data = col_int32_get(col_int32, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(col_int32_data[i] == int32_data[i]);
    col_free(col_int32);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(size);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", size);
    const uint8_t *col_uint8_data = col_uint8_get(col_uint8, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(col_uint8_data[i] == uint8_data[i]);
    col_free(col_uint8);
    free(uint8_data);

    char **string_data = col_string_data_create(size);
    struct col *col_string = col_string_dummy_create("string", size);
    const char **col_string_data = col_string_get(col_string, &err);
    assert(err == COL_ERR_OK);
    for (size_t i = 0; i < size; i++)
        assert(strcmp(col_string_data[i], string_data[i]) == 0);
    col_free(col_string);
    for (size_t i = 0; i < size; i++)
        free(string_data[i]);
    free(string_data);

    /* err */
    struct col *col_valid = col_double_dummy_create("valid", 999);

    assert(col_float_get(col_valid, &err) == NULL);
    assert(err == COL_ERR_INVALID_DTYPE);

    col_free(col_valid);
}
