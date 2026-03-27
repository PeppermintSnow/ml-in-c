#ifndef COL_CORE_TYPE_H
#define COL_CORE_TYPE_H

#include <stddef.h>

/* enums */

/**
 * @brief Error codes for `column_t` helper functions.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
typedef enum col_err {
    COL_ERR_OK = 0,         /**< No errors*/
    COL_ERR_IO,
    COL_ERR_OOM,
    COL_ERR_NO_DATA,
    COL_ERR_OUT_OF_BOUNDS,
    COL_ERR_INVALID_DTYPE,
    COL_ERR_EMPTY_NAME,
    COL_ERR_NOT_FOUND,
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
    COL_DTYPE_DOUBLE = 0,   /**< C double (64-bit double-precision float) */
    COL_DTYPE_FLOAT,        /**< C float (32-bit single-precision float) */
    COL_DTYPE_INT64,        /**< int64_t (64-bit signed integer) */
    COL_DTYPE_INT32,        /**< int32_t (32-bit signed integer) */
    COL_DTYPE_UINT8,        /**< uint8_t (8-bit unsigned integer) */
    COL_DTYPE_STRING        /**< char* (null-terminated string) */
} col_dtype_t;

/* structs */

/**
 * @brief Represents a column containing an array of data in a dataframe.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
typedef struct col {
    char *name;                 /**< Name of the column*/
    void *data;                 /**< Array of data in the column*/
    size_t n_rows;              /**< Number of rows*/
    const col_dtype_t dtype;    /**< Datatype  of the column*/
    const size_t stride;        /**< Byte offset of the datatype*/
} col_t;

#endif
