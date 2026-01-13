#ifndef DATAFRAME_CORE_H
#define DATAFRAME_CORE_H

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
 *      double data[] = {1, 2, 3};
 *      DataFrame *df = DF_fromArray(data, 3, "feature1");
 * 
 *      // Add a column
 *      double newData[] = {4, 5, 6};
 *      DF_addColumn(df, newData, "feature2");
 *
 *      // Free array from memory
 *      DF_free(df);
 *
 *      return 0;
 * }
 * @endcode
 */
typedef struct {
    double *data;           /**< Flattened array */
    int numRows;            /**< Number of rows (samples) */    
    int numCols;            /**< Number of columns (features) per row */
    char **featureNames;    /**< Array of column/feature names */
} DataFrame;

/**
 * @brief Creates a DataFrame with one feature from the given array.
 *
 * @param data Pointer to the source array.
 * @param numRows Number of rows/samples in the source array.
 * @param name Name of the column/feature.
 * @return Pointer to the newly created DataFrame.
 * @note Caller is responsible for freeing allocated memory.
 * @see DF_free() to free the DataFrame.
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
 *      DataFrame *df = DF_fromArray(data, 3, "feature1");
 *
 *      return 0;
 * }
 * @endcode
 */
DataFrame *DF_fromArray(double *data, int numRows, char *name);

/**
 * @brief Adds a single column/feature to an existing DataFrame.
 *
 * @param df Pointer to the existing DataFrame to add the column on.
 * @param data Pointer to the source array containing the new data to be added.
 * @param name Name of the new column/feature.
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
 *      DataFrame *df = DF_fromArray(data, 3, "feature1");
 *      
 *      // Add a column to the existing DataFrame
 *      double newData[] = {4, 5, 6};
 *      DF_addColumn(df, newData, "feature2");
 *
 *      return 0;
 * }
 */
int DF_addColumn(DataFrame *df, double *data, char *name);

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
 *      DataFrame *df = DF_fromArray(data, 3, "feature1");
 *      
 *      // Free DataFrame from allocated memory
 *      DF_free(df);
 *
 *      return 0;
 * }
 */
void DF_free(DataFrame *df);
#endif
