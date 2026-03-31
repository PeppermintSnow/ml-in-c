#ifndef COL_CORE_MODIFIERS_H
#define COL_CORE_MODIFIERS_H

#include "dtypes/col/core/type.h"
#include <stdint.h>

/**
 * @brief Modifies the value at the specified index.
 *
 * This serves as a generic setter for internal use.
 * Use the type-safe setters instead.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-29
 */
int col_set(col_t *col, const void *val, const size_t idx);

/**
 * @brief Modifies the value at the specified index. Used for `double` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_double_set(col_t *col, const double val, const size_t idx) {
    if (col->dtype != COL_DTYPE_DOUBLE)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, &val, idx);
}

/**
 * @brief Modifies the value at the specified index. Used for `float` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_float_set(col_t *col, const float val, const size_t idx) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, &val, idx);
}

/**
 * @brief Modifies the value at the specified index. Used for `int64` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_int64_set(col_t *col, const int64_t val, const size_t idx) {
    if (col->dtype != COL_DTYPE_INT64)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, &val, idx);
}

/**
 * @brief Modifies the value at the specified index. Used for `int32` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_int32_set(col_t *col, const int32_t val, const size_t idx) {
    if (col->dtype != COL_DTYPE_INT32)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, &val, idx);
}

/**
 * @brief Modifies the value at the specified index. Used for `uint8` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_uint8_set(col_t *col, const uint8_t val, const size_t idx) {
    if (col->dtype != COL_DTYPE_UINT8)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, &val, idx);
}

/**
 * @brief Modifies the value at the specified index. Used for `string` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to set it to.
 * @param idx Target index to modify.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-31
 */
static inline int col_string_set(col_t *col, const char *val, const size_t idx) {
    if (col->dtype != COL_DTYPE_STRING)
        return COL_ERR_INVALID_DTYPE;
    return col_set(col, val, idx);
}

/**
 * @brief Appends a value to the `col_t`'s data.
 *
 * This serves as a generic append function for internal use.
 * Use the type-safe append functions instead.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_append(col_t *col, const void *val);

/**
 * @brief Appends a value to the `col_t`'s data. Used for `double` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_double_append(col_t *col, const double val) {
    if (col->dtype != COL_DTYPE_DOUBLE)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, &val);
}

/**
 * @brief Appends a value to the `col_t`'s data. Used for `float` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_float_append(col_t *col, const float val) {
    if (col->dtype != COL_DTYPE_FLOAT)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, &val);
}

/**
 * @brief Appends a value to the `col_t`'s data. Used for `int64` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_int64_append(col_t *col, const int64_t val) {
    if (col->dtype != COL_DTYPE_INT64)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, &val);
}

/**
 * @brief Appends a value to the `col_t`'s data. Used for `int32` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_int32_append(col_t *col, const int32_t val) {
    if (col->dtype != COL_DTYPE_INT32)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, &val);
}

/**
 * @brief Appends a value to the `col_t`'s data. Used for `uint8` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_uint8_append(col_t *col, const uint8_t val) {
    if (col->dtype != COL_DTYPE_UINT8)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, &val);
}

/**
 * @brief Appends a value to the `col_t`'s data. Used for `string` dtypes.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
static inline int col_string_append(col_t *col, const char *val) {
    if (col->dtype != COL_DTYPE_STRING)
        return COL_ERR_INVALID_DTYPE;
    return col_append(col, val);
}

/**
 * @brief Removes the specified index from the `col_t`'s data.
 *
 * @param col Target `col_t` to modify.
 * @param idx Target index to remove in the col parameter.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_remove(col_t *col, const size_t idx);

/**
 * @brief Renames a `col_t`'s `name` property.
 *
 * @param col Target `col_t` to modify.
 * @param idx Target index to remove in the col parameter.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_rename(col_t *col, const char *name);

#endif
