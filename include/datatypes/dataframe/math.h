#ifndef DATAFRAME_MATH_H
#define DATAFRAME_MATH_H

#include "./core.h"

/**
 * @brief Performs row-wise addition of col1 to col2.
 *
 * @param df Pointer to the target DataFrame.
 * @param col1 Name of the first addend column.
 * @param col2 Name of the second addend column.
 * @return Array of sums. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-28
 */
double *df_col_add(dataframe_t *df, const char *col1, const char *col2);

/**
 * @brief Performs row-wise subtraction of col2 from col1.
 *
 * @param df Pointer to the target DataFrame.
 * @param col1 Name of the minuend column.
 * @param col2 Name of the subtrahend column.
 * @return Array of differences. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-28
 */
double *df_col_sub(dataframe_t *df, const char *col1, const char *col2);

/**
 * @brief Performs row-wise multiplication of col1 with col2.
 *
 * @param df Pointer to the target DataFrame.
 * @param col1 Name of the multiplicand column.
 * @param col2 Name of the multiplier column.
 * @return Array of products. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-28
 */
double *df_col_mul(dataframe_t *df, const char *col1, const char *col2);

/**
 * @brief Performs row-wise division of col1 over col2.
 *
 * @param df Pointer to the target DataFrame.
 * @param col1 Name of the numerator column.
 * @param col2 Name of the denominator column.
 * @return Array of quotients. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-02-28
 */
double *df_col_div(dataframe_t *df, const char *col1, const char *col2);

/**
 * @brief Adds the scalar value to each row of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @param scalar Scalar value to add to each row of the column.
 * @return Array of sums. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double *df_col_add_s(dataframe_t *df, const char *col, const double scalar);

/**
 * @brief Subtracts the scalar value from each row of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @param scalar Scalar value to subtract from each row of the column.
 * @return Array of differences. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double *df_col_sub_s(dataframe_t *df, const char *col, const double scalar);

/**
 * @brief Multiplies the scalar value with each row of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @param scalar Scalar value to multiply each row of the column.
 * @return Array of products. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double *df_col_mul_s(dataframe_t *df, const char *col, const double scalar);

/**
 * @brief Divides each row of the target column by the scalar value.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @param scalar Scalar value to divide each row of the column.
 * @return Array of quotients. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double *df_col_div_s(dataframe_t *df, const char *col, const double scalar);

/**
 * @brief Computes the mean of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Mean value. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_mean(dataframe_t *df, const char *col);

/**
 * @brief Computes the sum of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Sum of all rows. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_sum(dataframe_t *df, const char *col);

/**
 * @brief Finds the minimum value in the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Minimum value. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_min(dataframe_t *df, const char *col);

/**
 * @brief Finds the maximum value in the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Maximum value. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_max(dataframe_t *df, const char *col);

/**
 * @brief Computes the population variance of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Population variance. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_var(dataframe_t *df, const char *col);

/**
 * @brief Computes the standard deviation of the target column.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Name of the target column.
 * @return Standard deviation. NAN on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
double df_col_std(dataframe_t *df, const char *col);

#endif
