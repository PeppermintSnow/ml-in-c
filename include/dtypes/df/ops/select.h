#ifndef DATAFRAME_SELECT_H
#define DATAFRAME_SELECT_H

#include "../core.h"

/**
 * @brief Keeps only the specified columns in the DataFrame.
 *
 * @param df Pointer to the target DataFrame.
 * @param cols Array of column names to keep.
 * @param n_cols Length of the `cols` parameter.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-12
 */
int df_col_select(dataframe_t *df, const char **cols, const size_t n_cols);

/**
 * @brief Keeps only the range of rows in the DataFrame.
 *
 * @param df Pointer to the target DataFrame.
 * @param start Index to slice from.
 * @param end Index to slice to.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-12
 */
int df_row_select(dataframe_t *df, const size_t start, const size_t end);

#endif
