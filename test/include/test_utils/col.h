#ifndef COL_TEST_UTILS_H
#define COL_TEST_UTILS_H

#include <stddef.h>
#include <stdint.h>

#include "dtypes/col/core/type.h"

double *col_double_data_create(const size_t n);
float *col_float_data_create(const size_t n);
int64_t *col_int64_data_create(const size_t n);
int32_t *col_int32_data_create(const size_t n);
uint8_t *col_uint8_data_create(const size_t n);
char **col_string_data_create(const size_t n);

col_t *col_double_dummy_create(const char *name, const size_t n_rows);
col_t *col_float_dummy_create(const char *name, const size_t n_rows);
col_t *col_int64_dummy_create(const char *name, const size_t n_rows);
col_t *col_int32_dummy_create(const char *name, const size_t n_rows);
col_t *col_uint8_dummy_create(const char *name, const size_t n_rows);
col_t *col_string_dummy_create(const char *name, const size_t n_rows);

#endif

