#include "./core.h"

#ifndef DATAFRAME_MATH_H
#define DATAFRAME_MATH_H

/**
 * @brief Performs row-wise addition of col1 to col2.
 *
 * @param df Pointer to the target DataFrame.
 * @param col1 Name of the first column.
 * @param col2 Name of the second column to add to the first.
 * @return Array of doubles containing the sum of each row. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-28
 */
double *df_col_add(dataframe_t *df, const char *col1, const char *col2);

#endif
