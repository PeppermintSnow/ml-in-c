#ifndef DATAFRAME_OPS_H
#define DATAFRAME_OPS_H

#include <stdint.h>
#include "./core.h"

/**
 * @brief Represents a boolean mask for filtering DataFrames.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-07
 */
typedef struct df_mask {
    uint8_t *data;  /**< Boolean array containing 0x00 or 0xFF*/
    size_t n_rows;  /**< Total number of rows, inherited target DataFrame*/
    size_t n_keep;  /**< Number of 0xFF values in data*/
} df_mask_t;


/**
 * @brief Comparison enumerables for DataFrame masking functions.
 *
 * @see df_mask_or() for use with logical OR filtering.
 * @see df_mask_and() for use with logical AND filtering.
 * 
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-07
 */
typedef enum {
    DF_MASK_EQ = 0, /**< Equal to (==)*/
    DF_MASK_NE,     /**< Not equal to (!=)*/
    DF_MASK_LT,     /**< Less than (<)*/
    DF_MASK_GT,     /**< Greater than (>)*/
    DF_MASK_LE,     /**< Less than or equal to (<=)*/
    DF_MASK_GE      /**< Greater than or equal to (>=)*/
} df_mask_comparison_t;

/**
 * @brief Instantiates a boolean mask of length n_rows.
 * 
 * @param n_rows Row count of target DataFrame.
 * @param err_out Optional pointer to receive the error code.
 * @return Mask with n_rows initialized to 0xFF.
 * @note Caller is responsible for freeing allocated memory.
 * @see df_mask_free() to free the mask.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-07
 */
df_mask_t *df_mask_create(const int n_rows, int *err_out);

/**
 * @brief Applies an OR gate to the current mask data.
 * 
 * @param mask Pointer to existing mask that will be modified.
 * @param df Pointer to DataFrame containing the data to compare.
 * @param col Name of the column in the DataFrame.
 * @param comp Comparison operator enumerable. (e.g., DF_MASK_EQUAL).
 * @param value Value to be compared against.
 * @return 0 on success, non-zero on failure.
 * @see df_mask_comparison_t for valid comparison parameters.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-07
 */
int df_mask_or(
    df_mask_t *mask,
    const dataframe_t *df,
    const char *col,
    const df_mask_comparison_t comp,
    const double value
);

/**
 * @brief Applies an AND gate to the current mask data.
 * 
 * @param mask Pointer to existing mask that will be modified.
 * @param df Pointer to DataFrame containing the data to compare.
 * @param col Name of the column in the DataFrame.
 * @param comp Comparison operator enumerable. (e.g., DF_MASK_EQUAL).
 * @param value Value to be compared against.
 * @return 0 on success, non-zero on failure.
 * @see df_mask_comparison_t for valid comparison parameters.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-07
 */
int df_mask_and(
    df_mask_t *mask,
    const dataframe_t *df,
    const char *col,
    const df_mask_comparison_t comp,
    const double value
);

/**
 * @brief Applies the given mask on a DataFrame.
 * 
 * @param df Pointer to the target DataFrame.
 * @param mask Pointer to the mask.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-07
 */
int df_mask_apply(dataframe_t *df, const df_mask_t *mask);

/**
 * @brief Frees all allocated memory by the mask.
 *
 * @param mask Pointer to the mask to free.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-07
 */
int df_mask_free(df_mask_t *mask);

#endif
