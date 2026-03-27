#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dtypes/col/core/lifecycle.h"
#include "dtypes/col/core/type.h"
#include "test_utils/col.h"

double *col_double_data_create(const size_t n) {
    double *data = malloc(n * sizeof(double));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i * 3.141592653589793;

    return data;
}

float *col_float_data_create(const size_t n) {
    float *data = malloc(n * sizeof(float));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i * 3.1415926;

    return data;
}

int64_t *col_int64_data_create(const size_t n) {
    int64_t *data = malloc(n * sizeof(int64_t));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i * 64;

    return data;
}

int32_t *col_int32_data_create(const size_t n) {
    int32_t *data = malloc(n * sizeof(int32_t));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i * 32;

    return data;
}

uint8_t *col_uint8_data_create(const size_t n) {
    uint8_t *data = malloc(n * sizeof(uint8_t));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
        data[i] = i % 256;

    return data;
}

char **col_string_data_create(const size_t n) {
    char **data = malloc(n * sizeof(char *));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++) {
        char buf[32];
        sprintf(buf, "Entry %zu", i);
        data[i] = strdup(buf);
        if (!data[i]) {
            for (size_t j = 0; j < i; j++)
                free(data[j]);
            free(data);
            return NULL;
        }
    }

    return data;
}

col_t *col_double_dummy_create(const char *name, const size_t n_rows) {
    double *data = col_double_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_DOUBLE, 
        NULL
    );
    if (data)
		free(data);
    return col;
}

col_t *col_float_dummy_create(const char *name, const size_t n_rows) {
    float *data = col_float_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_FLOAT, 
        NULL
    );
    if (data)
		free(data);
    return col;
}

col_t *col_int64_dummy_create(const char *name, const size_t n_rows) {
    int64_t *data = col_int64_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_INT64, 
        NULL
    );
    if (data)
		free(data);
    return col;
}

col_t *col_int32_dummy_create(const char *name, const size_t n_rows) {
    int32_t *data = col_int32_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_INT32, 
        NULL
    );
    if (data)
		free(data);
    return col;
}

col_t *col_uint8_dummy_create(const char *name, const size_t n_rows) {
    uint8_t *data = col_uint8_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_UINT8, 
        NULL
    );
    if (data)
		free(data);
    return col;
}

col_t *col_string_dummy_create(const char *name, const size_t n_rows) {
    char **data = col_string_data_create(n_rows);
    struct col *col = col_create_array(
        name, 
        data, 
        n_rows, 
        COL_DTYPE_STRING, 
        NULL
    );

    if (data) {
        for (size_t i = 0; i < n_rows; i++) {
            if (data[i])
                free(data[i]);
        }
		free(data);
    }

    return col;
}
