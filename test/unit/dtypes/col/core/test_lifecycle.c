#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "dtypes/col/core/type.h"
#include "dtypes/col/core/lifecycle.h"
#include "dtypes/col/core/internal.h"
#include "test_utils/col.h"

void test_col_create();
void test_col_create_array();
void test_col_clone();
void test_col_free();

static void col_assert(
    const col_t *col, 
    const char *name,
    const void *data,
    const size_t n_rows, 
    const col_dtype_t dtype,
    const int err
);

static const size_t SIZE = 999;

int main() {
    test_col_create();
    test_col_create_array();
    test_col_clone();
    test_col_free();
}

void test_col_create() {
    int err = 0;

    /* valid */
    struct col *col_double = col_create("double", COL_DTYPE_DOUBLE, &err);
    col_assert(col_double, "double", NULL, 0, COL_DTYPE_DOUBLE, err);
    col_free(col_double);

    struct col *col_float = col_create("float", COL_DTYPE_FLOAT, &err);
    col_assert(col_float, "float", NULL, 0, COL_DTYPE_FLOAT, err);
    col_free(col_float);

    struct col *col_int64 = col_create("int64", COL_DTYPE_INT64, &err);
    col_assert(col_int64, "int64", NULL, 0, COL_DTYPE_INT64, err);
    col_free(col_int64);

    struct col *col_int32 = col_create("int32", COL_DTYPE_INT32, &err);
    col_assert(col_int32, "int32", NULL, 0, COL_DTYPE_INT32, err);
    col_free(col_int32);

    struct col *col_uint8 = col_create("uint8", COL_DTYPE_UINT8, &err);
    col_assert(col_uint8, "uint8", NULL, 0, COL_DTYPE_UINT8, err);
    col_free(col_uint8);

    struct col *col_string = col_create("string", COL_DTYPE_STRING, &err);
    col_assert(col_string, "string", NULL, 0, COL_DTYPE_STRING, err);
    col_free(col_string);

    /* err */
    struct col *col_bad_dtype = col_create("bad_dtype", 999, &err);
    assert(col_bad_dtype == NULL);
    assert(err == COL_ERR_INVALID_DTYPE);

    struct col *col_blank_name = col_create("", COL_DTYPE_DOUBLE, &err);
    assert(col_blank_name == NULL);
    assert(err == COL_ERR_EMPTY_NAME);

    struct col *col_null_name = col_create(NULL, COL_DTYPE_DOUBLE, &err);
    assert(col_null_name == NULL);
    assert(err == COL_ERR_EMPTY_NAME);
}

void test_col_create_array() {
    int err = 0;

    /* valid */
    double *double_data = col_double_data_create(SIZE);
    struct col *col_double = col_double_dummy_create("double", SIZE);
    col_assert(col_double, "double", double_data, SIZE, COL_DTYPE_DOUBLE, err);
    free(double_data);
    col_free(col_double);

    float *float_data = col_float_data_create(SIZE);
    struct col *col_float = col_float_dummy_create("float", SIZE);
    col_assert(col_float, "float", float_data, SIZE, COL_DTYPE_FLOAT, err);
    free(float_data);
    col_free(col_float);

    int64_t *int64_data = col_int64_data_create(SIZE);
    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    col_assert(col_int64, "int64", int64_data, SIZE, COL_DTYPE_INT64, err);
    free(int64_data);
    col_free(col_int64);

    int32_t *int32_data = col_int32_data_create(SIZE);
    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    col_assert(col_int32, "int32", int32_data, SIZE, COL_DTYPE_INT32, err);
    free(int32_data);
    col_free(col_int32);

    uint8_t *uint8_data = col_uint8_data_create(SIZE);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    col_assert(col_uint8, "uint8", uint8_data, SIZE, COL_DTYPE_UINT8, err);
    free(uint8_data);
    col_free(col_uint8);

    char **string_data = col_string_data_create(SIZE);
    struct col *col_string = col_string_dummy_create("char", SIZE);
    col_assert(col_string, "char", string_data, SIZE, COL_DTYPE_STRING, err);
    for (size_t i = 0; i < SIZE; i++)
        free(string_data[i]);
    free(string_data);
    col_free(col_string);

    /* err */
    double *data = col_double_data_create(SIZE);

    struct col *col_null_name = col_create_array(NULL, data, SIZE, COL_DTYPE_DOUBLE, &err);
    assert(col_null_name == NULL);
    assert(err == COL_ERR_EMPTY_NAME);

    struct col *col_blank_name = col_create_array("", data, SIZE, COL_DTYPE_DOUBLE, &err);
    assert(col_blank_name == NULL);
    assert(err == COL_ERR_EMPTY_NAME);

    struct col *col_empty_data = col_create_array("no_data", NULL, SIZE, COL_DTYPE_DOUBLE, &err);
    assert(col_empty_data == NULL);
    assert(err == COL_ERR_NO_DATA);

    struct col *col_bad_rows = col_create_array("bad_rows", data, 0, COL_DTYPE_DOUBLE, &err);
    assert(col_bad_rows == NULL);
    assert(err == COL_ERR_NO_DATA);

    struct col *col_bad_dtype = col_create_array("bad_dtype", data, 0, 999, &err);
    assert(col_bad_dtype == NULL);
    assert(err == COL_ERR_INVALID_DTYPE);

    free(data);
}

void test_col_clone() {
    int err = 0;

    /* valid */
    double *double_data = col_double_data_create(SIZE);
    struct col *col_double = col_double_dummy_create("double", SIZE);
    struct col *col_double_clone = col_clone(col_double, &err);
    col_free(col_double);
    col_assert(
        col_double_clone,
        "double",
        double_data,
        SIZE,
        COL_DTYPE_DOUBLE,
	    err
    );
    col_free(col_double_clone);
    free(double_data);

    float *float_data = col_float_data_create(SIZE);
    struct col *col_float = col_float_dummy_create("float", SIZE);
    struct col *col_float_clone = col_clone(col_float, &err);
    col_free(col_float);
    col_assert(
        col_float_clone,
        "float",
        float_data,
        SIZE,
        COL_DTYPE_FLOAT,
	    err
    );
    col_free(col_float_clone);
    free(float_data);

    int64_t *int64_data = col_int64_data_create(SIZE);
    struct col *col_int64 = col_int64_dummy_create("int64", SIZE);
    struct col *col_int64_clone = col_clone(col_int64, &err);
    col_free(col_int64);
    col_assert(
        col_int64_clone,
        "int64",
        int64_data,
        SIZE,
        COL_DTYPE_INT64,
	    err
    );
    col_free(col_int64_clone);
    free(int64_data);

    int32_t *int32_data = col_int32_data_create(SIZE);
    struct col *col_int32 = col_int32_dummy_create("int32", SIZE);
    struct col *col_int32_clone = col_clone(col_int32, &err);
    col_free(col_int32);
    col_assert(
        col_int32_clone,
        "int32",
        int32_data,
        SIZE,
        COL_DTYPE_INT32,
	    err
    );
    col_free(col_int32_clone);
    free(int32_data);

    uint8_t *uint8_data = col_uint8_data_create(SIZE);
    struct col *col_uint8 = col_uint8_dummy_create("uint8", SIZE);
    struct col *col_uint8_clone = col_clone(col_uint8, &err);
    col_free(col_uint8);
    col_assert(
        col_uint8_clone,
        "uint8",
        uint8_data,
        SIZE,
        COL_DTYPE_UINT8,
	    err
    );
    col_free(col_uint8_clone);
    free(uint8_data);

    char **string_data = col_string_data_create(SIZE);
    struct col *col_string = col_string_dummy_create("string", SIZE);
    struct col *col_string_clone = col_clone(col_string, &err);
    col_free(col_string);
    col_assert(
        col_string_clone,
        "string",
        string_data,
        SIZE,
        COL_DTYPE_STRING,
	    err
    );
    col_free(col_string_clone);
    for (size_t i = 0; i < SIZE; i++)
        free(string_data[i]);
    free(string_data);

    /* err */
    struct col *col_valid1 = col_double_dummy_create("valid1", SIZE);
    struct col *col_valid2 = col_clone(col_valid1, &err);
    assert(err == COL_ERR_OK);
    struct col *col_valid3 = col_clone(col_valid1, &err);
    assert(err == COL_ERR_OK);

    struct col *col_null = col_clone(NULL, &err);
    assert(col_null == NULL);
    assert(err == COL_ERR_NO_DATA);

    free(col_valid1->data);
    col_valid1->data = NULL;
    struct col *col_null_data = col_clone(col_valid1, &err);
    assert(col_null_data == NULL);
    assert(err == COL_ERR_NO_DATA);
    col_free(col_valid1);

    free(col_valid2->name);
    col_valid2->name = NULL;
    struct col *col_null_name = col_clone(col_valid2, &err);
    assert(col_null_name == NULL);
    assert(err == COL_ERR_EMPTY_NAME);
    col_free(col_valid2);

    col_valid3->n_rows = 0;
    struct col *col_bad_rows = col_clone(col_valid3, &err);
    assert(col_bad_rows == NULL);
    assert(err == COL_ERR_NO_DATA);
    col_free(col_valid3);
}

void test_col_free() {
    struct col *col = col_double_dummy_create("col", SIZE);
    assert(col_free(col) == COL_ERR_OK);
}

static void col_assert(
    const col_t *col, 
    const char *name,
    const void *data,
    const size_t n_rows, 
    const col_dtype_t dtype,
    const int err
) {
    const size_t stride = col_dtype_stride(dtype);

    assert(err == COL_ERR_OK);
    assert(strcmp(col->name, name) == 0);
    assert(col->n_rows == n_rows);
    assert(col->dtype == dtype);
    assert(col->stride == stride);

    if (!n_rows) {
        assert(col->data == NULL);
        return;
    }

    switch (col->dtype) {
        case COL_DTYPE_DOUBLE: {
            const double *exp = (const double *)data;
            const double *act = (const double *)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(fabs(exp[i] - act[i]) < 1e-12f);
            break;
        }
        case COL_DTYPE_FLOAT: {
            const float *exp = (const float *)data;
            const float *act = (const float *)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(fabsf(exp[i] - act[i]) < 1e-6f);
            break;
        }
        case COL_DTYPE_INT64: {
            const int64_t *exp = (const int64_t *)data;
            const int64_t *act = (const int64_t *)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(exp[i] == act[i]);
            break;
        }
        case COL_DTYPE_INT32: {
            const int32_t *exp = (const int32_t *)data;
            const int32_t *act = (const int32_t *)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(exp[i] == act[i]);
            break;
        }
        case COL_DTYPE_UINT8: {
            const uint8_t *exp = (const uint8_t *)data;
            const uint8_t *act = (const uint8_t *)col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(exp[i] == act[i]);
            break;
        }
        case COL_DTYPE_STRING: {
            const char **exp = (const char **)data;
            char **act = col->data;
            for (size_t i = 0; i < col->n_rows; i++)
                assert(strcmp(act[i], exp[i]) == 0);
            break;
        }
    }
}
