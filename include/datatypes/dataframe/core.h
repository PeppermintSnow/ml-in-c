#include <stddef.h>

#ifndef DATAFRAME_CORE_H
#define DATAFRAME_CORE_H

/**
 * Error Codes
 */
typedef enum {
    DF_OK = 0,
    DF_ERR_DUPLICATE_COLUMN,
    DF_ERR_NONEXISTENT_COLUMN,
    DF_ERR_NONEXISTENT_ROW,
    DF_ERR_LAST_COLUMN,
    DF_ERR_LAST_ROW,
    DF_ERR_ROW_MISMATCH,
    DF_ERR_COLUMN_MISMATCH
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
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create from array
 *      double column1[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(column1, 3, "feature1");
 * 
 *      // Add a column
 *      double column2[] = {4, 5, 6};
 *      df_column_add(df, column2, "feature2");
 *
 *      // Free from memory
 *      df_free(df);
 *
 *      return 0;
 * }
 * @endcode
 */
typedef struct dataframe {
    double *data;           /**< Flattened array */
    char **columns;         /**< Array of column names */
    size_t n_rows;          /**< Number of rows */    
    size_t n_columns;          /**< Number of columns */
} dataframe_t;

/**
 * @brief Creates a DataFrame with one feature from the given array.
 *
 * @param data Pointer to the source array.
 * @param n_rows Number of rows/samples in the source array.
 * @param column_name Name of the column.
 * @return Pointer to the newly created DataFrame.
 * @note Caller is responsible for freeing allocated memory.
 * @see df_free() to free the DataFrame.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *
 *      return 0;
 * }
 * @endcode
 */
dataframe_t *df_create_from_array(const double *data, const size_t n_rows, const char *column_name);

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
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      // Add a column to the existing DataFrame
 *      double new_data[] = {4, 5, 6};
 *      df_column_add(df, new_data, "feature2");
 *
 *      return 0;
 * }
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
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      // Add a column to the existing DataFrame
 *      double new_data[] = {4, 5, 6};
 *      df_column_add(df, new_data, "feature2");
 *
 *      // Delete column "feature1"
 *      df_column_delete(df, "feature1");
 *
 *      return 0;
 * }
 */
int df_column_delete(dataframe_t *df, const char *column_name);

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
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      // Add a column to the existing DataFrame
 *      double new_column[] = {4, 5, 6};
 *      df_column_add(df, new_column, "feature2");
 *
 *      // Add row
 *      double new_row[] = {7, 8};
 *      df_row_add(df, new_row);
 *
 *      return 0;
 * }
 */
int df_row_add(dataframe_t *df, const double *data, const size_t n_columns);

/**
 * @brief Deletes a row/entry from a DataFrame.
 *
 * @param df Pointer to the existing DataFrame to remove the row from.
 * @param index Index of the row to be deleted.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-20
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      // Add a column to the existing DataFrame
 *      double new_column[] = {4, 5, 6};
 *      df_column_add(df, new_column, "feature2");
 *
 *      // Delete row 2
 *      df_row_delete(df, 2);
 *
 *      return 0;
 * }
 */
int df_row_delete(dataframe_t *df, const size_t index);

/**
 * @brief Displays the DataFrame in a table.
 *
 * @param df Pointer to the DataFrame to display.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      df_display(df);
 *
 *      return 0;
 * }
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
 *
 * @code
 * #include <ml-in-c/datatypes/dataframe.h>
 *
 * int main() {
 *      // Create a DataFrame from an array
 *      double data[] = {1, 2, 3};
 *      dataframe_t *df = df_create_from_array(data, 3, "feature1");
 *      
 *      // Free DataFrame from allocated memory
 *      df_free(df);
 *
 *      return 0;
 * }
 */
void df_free(dataframe_t *df);
#endif
