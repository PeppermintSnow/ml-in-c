#ifndef DF_CORE_ENUM_H
#define DF_CORE_ENUM_H

/**
 * @brief Error codes for `df_t` helper functions.
 *
 * @see df_strerr() to convert the error codes to messages.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
typedef enum df_error {
    DF_OK = 0,          /**< No errors*/
    DF_COL_EXISTS,      /**< Column already exists*/
    DF_NO_COL,          /**< Column not found*/
    DF_NO_ROW,          /**< Row not found*/
    DF_LAST_COL,        /**< Cannot delete last column*/
    DF_LAST_ROW,        /**< Cannot delete last row*/
    DF_ROW_MISMATCH,    /**< Data length does not match df->n_rows*/
    DF_COL_MISMATCH,    /**< Data length does not match df->n_columns*/
    DF_IO,              /**< I/O error*/
    DF_OOM,             /**< Out of memory*/
    DF_BAD_ARG          /**< Bad argument*/
} df_error_t;

/**
 * @brief Datatypes for `df_col_t`.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
typedef enum df_col_type {
    DF_COL_TYPE_DOUBLE = 0,
    DF_COL_TYPE_STR,
    DF_COL_TYPE_INT,
    DF_COL_TYPE_UINT8,
} df_col_type_t;

#endif
