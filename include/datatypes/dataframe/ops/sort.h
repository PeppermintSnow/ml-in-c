#ifndef DATAFRAME_SORT_H
#define DATAFRAME_SORT_H

#include "../core.h"

/**
 * @brief Sorting order enumerables for DataFrame sorting.
 *
 * @see df_sort() for usage.
 * 
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-21
 */
typedef enum {
    DF_SORT_ASC = 0, /**< Ascending order */
    DF_SORT_DESC,    /**< Descending order */
} df_sort_order;

/**
 * @brief Sorts the DataFrame by specified columns in sequential order.
 *
 * @param df Pointer to the target DataFrame.
 * @param col Column name to sort by.
 * @param order Sorting order
 * @return 0 on success, non-zero on failure.
 * @see df_sort_order for a list of valid sorting order enumerables.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-03-21
 */
int df_sort(
    dataframe_t *df, 
    const char *col, 
    const df_sort_order order
);

#endif
