#include <stddef.h>

#ifndef DATAFRAME_CORE_H
#define DATAFRAME_CORE_H

/**
 * Error Codes
 */
typedef enum {
    DF_OK = 0,                  /**< No errors*/
    DF_ERR_DUPLICATE_COLUMN,    /**< Column already exists*/
    DF_ERR_NONEXISTENT_COLUMN,  /**< Column not found*/
    DF_ERR_NONEXISTENT_ROW,     /**< Row not found*/
    DF_ERR_LAST_COLUMN,         /**< Cannot delete last column*/
    DF_ERR_LAST_ROW,            /**< Cannot delete last row*/
    DF_ERR_ROW_MISMATCH,        /**< Data length does not match df->n_rows*/
    DF_ERR_COLUMN_MISMATCH      /**< Data length does not match df->n_columns*/
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
    size_t n_columns;       /**< Number of columns */
} dataframe_t;

/**
 * @brief Creates a DataFrame with one feature from the given array.
 *
 * @param data Pointer to the source array.
 * @param n_rows Number of rows/samples in the source array.
 * @param column_name Name of the column.
 * @return Pointer to the newly created DataFrame. NULL on error.
 * @note Caller is responsible for freeing allocated memory.
 * @see df_free() to free the DataFrame.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
dataframe_t *df_create_from_array(const double *data, const size_t n_rows, const char *column_name);

/**
 * @brief Fetch a target column from a DataFrame.
 *
 * @param df Pointer to the DataFrame to index.
 * @param column_name Target column to fetch.
 * @return Cloned DataFrame containing only the target column. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-27
 */
dataframe_t *df_column_get(dataframe_t *df, const char *column_name);

/**
 * @brief Adds a single column/feature to an existing DataFrame.
 *
 * @param df Pointer to the existing DataFrame to add the column on.
 * @param data Pointer to the source array containing the new data to be added.
 * @param n_rows Number of rows in the data to be added.
 * @param column_name Name of the new column.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
int df_column_add(dataframe_t *df, const double *data, const size_t n_rows, const char *column_name);

/**
 * @brief Deletes the specified column from a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to delete the column from.
 * @param column_name Name of the column/feature to be deleted.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 */
int df_column_delete(dataframe_t *df, const char *column_name);

/**
 * @brief Fetch a target index from a DataFrame.
 *
 * @param df Pointer to the DataFrame to index.
 * @param row_index Target row index to fetch.
 * @return Cloned DataFrame containing only the target row. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-27
 */
dataframe_t *df_row_get(dataframe_t *df, const size_t row_index);

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
int df_row_add(dataframe_t *df, const double *data, const size_t n_columns);

/**
 * @brief Deletes a row/entry from a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to remove the row from.
 * @param row_index Index of the row to be deleted.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 */
int df_row_delete(dataframe_t *df, const size_t row_index);

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
#endif
