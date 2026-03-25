#ifndef COL_CORE_ENUM_H
#define COL_CORE_ENUM_H

/**
 * @brief Error codes for `column_t` helper functions.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
typedef enum col_err {
    COL_OK = 0,         /**< No errors*/
    COL_OOM,
    COL_NO_DATA,
    COL_INVALID_DTYPE,
    COL_OUT_OF_BOUNDS,
} col_err_t;

/**
 * @brief Datatypes for `df_col_t`.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
typedef enum col_dtype {
    COL_DTYPE_DOUBLE = 0,
    COL_DTYPE_STR,
    COL_DTYPE_INT,
    COL_DTYPE_UINT8,
} col_dtype_t;

#endif
