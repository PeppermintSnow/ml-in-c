#ifndef COL_CORE_ACCESSORS_H
#define COL_CORE_ACCESSORS_H

#include <stdint.h>

#include "core/error.h"
#include "dtypes/col/core/type.h"

/**
 * @brief Accesses a C `double` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the C `double` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline double *col_double_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_DOUBLE)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return &((double *)col->data)[idx];
}

/**
 * @brief Accesses a C `float` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the C `float` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline float *col_float_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_DOUBLE)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return &((float *)col->data)[idx];
}

/**
 * @brief Accesses an `int64_t` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the `int64_t` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const int64_t *col_int64_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_INT64)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return &((const int64_t *)col->data)[idx];
}

/**
 * @brief Accesses an `int32_t` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the `int32_t` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const int32_t *col_int32_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_INT32)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return &((const int32_t *)col->data)[idx];
}

/**
 * @brief Accesses an `uint8_t` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the `uint8_t` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const uint8_t *col_uint8_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_UINT8)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return &((const uint8_t *)col->data)[idx];
}

/**
 * @brief Accesses a `char *` at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index of `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the `char *` at `col->data[idx]`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const char *col_string_at(
    const col_t *col, 
    const size_t idx,
    int *err_out
) {
    if (col->dtype != COL_DTYPE_STRING)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    if (idx >= col->n_rows)
        return mlc_fail_null(COL_ERR_OUT_OF_BOUNDS, err_out);
    return ((const char **)col->data)[idx];
}

/**
 * @brief Returns a read-only `double *` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `double *` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const double *col_double_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_DOUBLE)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const double *)col->data;
}

/**
 * @brief Returns a read-only `float *` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `float *` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const float *col_float_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const float *)col->data;
}

/**
 * @brief Returns a read-only `int64_t *` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `int64_t *` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const int64_t *col_int64_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const int64_t *)col->data;
}

/**
 * @brief Returns a read-only `int32_t *` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `int32_t *` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const int32_t *col_int32_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const int32_t *)col->data;
}

/**
 * @brief Returns a read-only `uint8_t *` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `uint8_t *` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const uint8_t *col_uint8_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const uint8_t *)col->data;
}

/**
 * @brief Returns a read-only `char **` data.
 *
 * @param col Target `col_t` to access.
 * @param err_out Optional pointer to receive error codes.
 * @return Typecasted `char **` pointer to `col->data`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-27
 */
static inline const char **col_string_get(const col_t *col, int *err_out) {
    if (col->dtype != COL_DTYPE_STRING)
        return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
    return (const char **)col->data;
}

#endif
