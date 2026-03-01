#ifndef DATAFRAME_CORE_H
#define DATAFRAME_CORE_H

#include <stddef.h>

/**
 * Error Codes
 */
typedef enum {
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
} dataframe_error_t;

/**
 * @brief Represents a matrix with names for each column.
 *
 * Data is stored as a row-major flattened array.
 * 
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
typedef struct dataframe {
    double *data;           /**< Flattened array */
    char **columns;         /**< Array of column names */
    size_t n_rows;          /**< Number of rows */    
    size_t n_cols;          /**< Number of columns */
} dataframe_t;

/**
 * @brief Creates a DataFrame with one feature from the given array.
 *
 * @param data Pointer to the source array.
 * @param n_rows Number of rows/samples in the source array.
 * @param col Name of the column.
 * @param err_out Optional pointer to receive the error code.
 * @return Pointer to the newly created DataFrame. NULL on error.
 * @note Caller is responsible for freeing allocated memory.
 * @see df_free() to free the DataFrame.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
dataframe_t *df_from_array(
    const double *data, 
    const size_t n_rows, 
    const char *col,
    int *err_out
);

/**
 * @brief Fetch a target column from a DataFrame.
 *
 * @param df Pointer to the DataFrame to index.
 * @param col Target column to fetch.
 * @param err_out Optional pointer to receive the error code.
 * @return Array containing values of target column. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-27
 */
double *df_col_get(const dataframe_t *df, const char *col, int *err_out);

/**
 * @brief Adds a single column/feature to an existing DataFrame.
 *
 * @param df Pointer to the existing DataFrame to add the column on.
 * @param data Pointer to the source array containing the new data to be added.
 * @param n_rows Number of rows in the data to be added.
 * @param col Name of the new column.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
int df_col_append(dataframe_t *df, const double *data, const size_t n_rows, const char *col);

/**
 * @brief Deletes the specified column from a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to delete the column from.
 * @param col Name of the column/feature to be deleted.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 */
int df_col_drop(dataframe_t *df, const char *col);

/**
 * @brief Fetch a target index from a DataFrame.
 *
 * @param df Pointer to the DataFrame to index.
 * @param row_idx Target row index to fetch.
 * @param err_out Optional pointer to receive the error code.
 * @return Array containing values of target row. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-27
 */
double *df_row_get(const dataframe_t *df, const size_t row_idx, int *err_out);

/**
 * @brief Adds a row/entry to a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to add the row to.
 * @param data Pointer to the source array containing the new data to be added.
 * @param n_columns Number of column in the data to be added.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 */
int df_row_append(dataframe_t *df, const double *data, const size_t n_columns);

/**
 * @brief Deletes a row/entry from a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to remove the row from.
 * @param row_idx Index of the row to be deleted.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 */
int df_row_drop(dataframe_t *df, const size_t row_idx);

/**
 * @brief Displays the DataFrame in a table.
 *
 * @param df Pointer to the DataFrame to display.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
void df_display(const dataframe_t *df);

/**
 * @brief Frees all allocated memory by the DataFrame.
 *
 * @param df Pointer to the DataFrame to free.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
void df_free(dataframe_t *df);

/**
 * @brief Converts DataFrame error codes to error messages.
 *
 * @param err Error code.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
const char *df_strerr(int err);

#endif
