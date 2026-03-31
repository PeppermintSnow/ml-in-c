#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <string.h>

#include "dtypes/col/core/accessors.h"
#include "dtypes/col/core/type.h"
#include "dtypes/col/core/lifecycle.h"
#include "dtypes/col/core/modifiers.h"
#include "test_utils/col.h"

void test_col_set();
void test_col_append();
void test_col_remove();
void test_col_rename();

static const size_t SIZE = 999;
static const size_t S_IDX = 0;
static const size_t M_IDX = SIZE / 2;
static const size_t E_IDX = SIZE - 1;

int main() {
    test_col_set();
    test_col_append();
    test_col_remove();
    test_col_rename();
}

void test_col_set() {
    /* valid */
    struct col *col_double = col_double_dummy_create("double", SIZE);
    assert(col_double_set(col_double, 3.141592653589, S_IDX) == COL_ERR_OK);
    assert(col_double_set(col_double, 3.141592653589, M_IDX) == COL_ERR_OK);
    assert(col_double_set(col_double, 3.141592653589, E_IDX) == COL_ERR_OK);
    assert(fabs(*col_double_at(col_double, S_IDX, NULL) - 3.141592653589) < 1e-12f);
    assert(fabs(*col_double_at(col_double, M_IDX, NULL) - 3.141592653589) < 1e-12f);
    assert(fabs(*col_double_at(col_double, E_IDX, NULL) - 3.141592653589) < 1e-12f);
    col_free(col_double);

    struct col *col_float = col_float_dummy_create("float", SIZE);
    assert(col_float_set(col_float, 3.141592, S_IDX) == COL_ERR_OK);
    assert(col_float_set(col_float, 3.141592, M_IDX) == COL_ERR_OK);
    assert(col_float_set(col_float, 3.141592, E_IDX) == COL_ERR_OK);
    assert(fabsf((float)(*col_float_at(col_float, S_IDX, NULL) - 3.141592)) < 1e-6f);
    assert(fabsf((float)(*col_float_at(col_float, M_IDX, NULL) - 3.141592)) < 1e-6f);
    assert(fabsf((float)(*col_float_at(col_float, E_IDX, NULL) - 3.141592)) < 1e-6f);
    col_free(col_float);

    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    assert(col_int64_set(col_int64, INT64_MAX - 1, S_IDX) == COL_ERR_OK);
    assert(col_int64_set(col_int64, INT64_MAX - 1, M_IDX) == COL_ERR_OK);
    assert(col_int64_set(col_int64, INT64_MAX - 1, E_IDX) == COL_ERR_OK);
	assert(*col_int64_at(col_int64, S_IDX, NULL) == INT64_MAX - 1);
	assert(*col_int64_at(col_int64, M_IDX, NULL) == INT64_MAX - 1);
	assert(*col_int64_at(col_int64, E_IDX, NULL) == INT64_MAX - 1);
    col_free(col_int64);

    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    assert(col_int32_set(col_int32, INT32_MAX - 1, S_IDX) == COL_ERR_OK);
    assert(col_int32_set(col_int32, INT32_MAX - 1, M_IDX) == COL_ERR_OK);
    assert(col_int32_set(col_int32, INT32_MAX - 1, E_IDX) == COL_ERR_OK);
	assert(*col_int32_at(col_int32, S_IDX, NULL) == INT32_MAX - 1);
	assert(*col_int32_at(col_int32, M_IDX, NULL) == INT32_MAX - 1);
	assert(*col_int32_at(col_int32, E_IDX, NULL) == INT32_MAX - 1);
    col_free(col_int32);

    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    assert(col_uint8_set(col_uint8, UINT8_MAX - 1, S_IDX) == COL_ERR_OK);
    assert(col_uint8_set(col_uint8, UINT8_MAX - 1, M_IDX) == COL_ERR_OK);
    assert(col_uint8_set(col_uint8, UINT8_MAX - 1, E_IDX) == COL_ERR_OK);
	assert(*col_uint8_at(col_uint8, S_IDX, NULL) == UINT8_MAX - 1);
	assert(*col_uint8_at(col_uint8, M_IDX, NULL) == UINT8_MAX - 1);
	assert(*col_uint8_at(col_uint8, E_IDX, NULL) == UINT8_MAX - 1);
    col_free(col_uint8);

    struct col *col_string = col_string_dummy_create("string", SIZE);
    assert(col_string_set(col_string, "foo", S_IDX) == COL_ERR_OK);
    assert(col_string_set(col_string, "bar", M_IDX) == COL_ERR_OK);
    assert(col_string_set(col_string, "baz", E_IDX) == COL_ERR_OK);
	assert(strcmp(col_string_at(col_string, S_IDX, NULL), "foo") == 0);
	assert(strcmp(col_string_at(col_string, M_IDX, NULL), "bar") == 0);
	assert(strcmp(col_string_at(col_string, E_IDX, NULL), "baz") == 0);
    col_free(col_string);

    /* err */
    struct col *col_valid1 = col_double_dummy_create("valid1", SIZE);
    assert(col_double_set(col_valid1, 3.141592653589, SIZE * 2) == COL_ERR_OUT_OF_BOUNDS);
    assert(col_float_set(col_valid1, 3.141592, S_IDX) == COL_ERR_INVALID_DTYPE);
    col_free(col_valid1);

    struct col *col_valid2 = col_string_dummy_create("valid2", SIZE);
    assert(col_string_set(col_valid2, NULL, S_IDX) == COL_ERR_NO_DATA);
    col_free(col_valid2);
}

void test_col_append() {
    /* valid */   
    struct col *col_double = col_double_dummy_create("double", SIZE);
    assert(col_double_append(col_double, 3.141592653589) == COL_ERR_OK);
    assert(col_double_append(col_double, 3.141592653589 * 2) == COL_ERR_OK);
    assert(col_double->n_rows == SIZE + 2);
    assert(fabs(*col_double_at(col_double, SIZE, NULL) - 3.141592653589) < 1e-12f);
    assert(fabs(*col_double_at(col_double, SIZE + 1, NULL) - 3.141592653589 * 2) < 1e-12f);
    col_free(col_double);

    struct col *col_float = col_float_dummy_create("float", SIZE);
    assert(col_float_append(col_float, 3.141592) == COL_ERR_OK);
    assert(col_float_append(col_float, 3.141592 * 2) == COL_ERR_OK);
    assert(col_float->n_rows == SIZE + 2);
    assert(fabsf((float)(*col_float_at(col_float, SIZE, NULL) - 3.141592)) < 1e-6f);
    assert(fabsf((float)(*col_float_at(col_float, SIZE + 1, NULL) - 3.141592 * 2)) < 1e-6f);
    col_free(col_float);

    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    assert(col_int64_append(col_int64, INT64_MAX - 1) == COL_ERR_OK);
    assert(col_int64_append(col_int64, INT64_MAX - 2) == COL_ERR_OK);
    assert(col_int64->n_rows == SIZE + 2);
    assert(*col_int64_at(col_int64, SIZE, NULL) == INT64_MAX - 1);
    assert(*col_int64_at(col_int64, SIZE + 1, NULL) == INT64_MAX - 2);
    col_free(col_int64);

    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    assert(col_int32_append(col_int32, INT32_MAX - 1) == COL_ERR_OK);
    assert(col_int32_append(col_int32, INT32_MAX - 2) == COL_ERR_OK);
    assert(col_int32->n_rows == SIZE + 2);
    assert(*col_int32_at(col_int32, SIZE, NULL) == INT32_MAX - 1);
    assert(*col_int32_at(col_int32, SIZE + 1, NULL) == INT32_MAX - 2);
    col_free(col_int32);

    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    assert(col_uint8_append(col_uint8, UINT8_MAX - 1) == COL_ERR_OK);
    assert(col_uint8_append(col_uint8, UINT8_MAX - 2) == COL_ERR_OK);
    assert(col_uint8->n_rows == SIZE + 2);
    assert(*col_uint8_at(col_uint8, SIZE, NULL) == UINT8_MAX - 1);
    assert(*col_uint8_at(col_uint8, SIZE + 1, NULL) == UINT8_MAX - 2);
    col_free(col_uint8);

    struct col *col_string = col_string_dummy_create("string", SIZE);
    assert(col_string_append(col_string, "foo") == COL_ERR_OK);
    assert(col_string_append(col_string, "bar") == COL_ERR_OK);
    assert(col_string->n_rows == SIZE + 2);
    assert(strcmp(col_string_at(col_string, SIZE, NULL), "foo") == 0);
    assert(strcmp(col_string_at(col_string, SIZE + 1, NULL), "bar") == 0);
    col_free(col_string);

    /* err */
    struct col *col_valid = col_string_dummy_create("valid", SIZE);
    assert(col_string_append(col_valid, NULL) == COL_ERR_NO_DATA);
    assert(col_float_append(col_valid, 3.141592) == COL_ERR_INVALID_DTYPE);
    col_free(col_valid);
}

void test_col_remove() {
    /* valid */   
    double *double_data = col_double_data_create(SIZE);
    struct col *col_double = col_double_dummy_create("double", SIZE);
    assert(col_remove(col_double, M_IDX) == COL_ERR_OK);
    assert(col_double->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_double->n_rows; i++)
        assert(fabs(*col_double_at(col_double, i, NULL) - double_data[i + 1]) < 1e-12f);
    col_free(col_double);
    free(double_data);

    float *float_data = col_float_data_create(SIZE);
    struct col *col_float = col_float_dummy_create("float", SIZE);
    assert(col_remove(col_float, M_IDX) == COL_ERR_OK);
    assert(col_float->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_float->n_rows; i++)
        assert(fabsf((float)(*col_float_at(col_float, i, NULL) - float_data[i + 1])) < 1e-6f);
    col_free(col_float);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(SIZE);
    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    assert(col_remove(col_int64, M_IDX) == COL_ERR_OK);
    assert(col_int64->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_int64->n_rows; i++)
        assert(*col_int64_at(col_int64, i, NULL) == int64_data[i + 1]);
    col_free(col_int64);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(SIZE);
    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    assert(col_remove(col_int32, M_IDX) == COL_ERR_OK);
    assert(col_int32->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_int32->n_rows; i++)
        assert(*col_int32_at(col_int32, i, NULL) == int32_data[i + 1]);
    col_free(col_int32);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(SIZE);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    assert(col_remove(col_uint8, M_IDX) == COL_ERR_OK);
    assert(col_uint8->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_uint8->n_rows; i++)
        assert(*col_uint8_at(col_uint8, i, NULL) == uint8_data[i + 1]);
    col_free(col_uint8);
    free(uint8_data);

    char **string_data = col_string_data_create(SIZE);
    struct col *col_string = col_string_dummy_create("string", SIZE);
    assert(col_remove(col_string, M_IDX) == COL_ERR_OK);
    assert(col_string->n_rows == SIZE - 1);
    for (size_t i = M_IDX; i < col_string->n_rows; i++)
        assert(strcmp(col_string_at(col_string, i, NULL), string_data[i + 1]) == 0);
    col_free(col_string);
    for (size_t i = 0; i < SIZE; i++)
        free(string_data[i]);
    free(string_data);

    /* err */
    struct col *col_valid = col_double_dummy_create("valid", SIZE);
    assert(col_remove(col_valid, SIZE + 1) == COL_ERR_OUT_OF_BOUNDS);
    col_free(col_valid);
}

void test_col_rename() {
    /* valid */
    struct col *col_valid = col_double_dummy_create("valid", SIZE);
    assert(col_rename(col_valid, "foo") == COL_ERR_OK);
    assert(strcmp(col_valid->name, "foo") == 0);

    /* err */
    assert(col_rename(col_valid, NULL) == COL_ERR_EMPTY_NAME);
    assert(strcmp(col_valid->name, "foo") == 0);
    col_free(col_valid);
}
