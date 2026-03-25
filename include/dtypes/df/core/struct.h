#ifndef DF_CORE_STRUCT_H
#define DF_CORE_STRUCT_H

#include <stddef.h>
#include "dtypes/df/core/enum.h"

/**
 * @brief Represents a column containing an array of data in a dataframe.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
typedef struct df_col {
    char *name;             /**< Name of the column*/
    void *data;             /**< Array of data in the column*/
    size_t n_rows;          /**< Number of rows*/
    df_col_type_t dtype;    /**< Datatype  of the column*/
} df_col_t;

/**
 * @brief Represents a matrix with names for each column.
 * 
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2025-09-14
 */
typedef struct df {
    df_col_t *cols;     /**< Array of columns */
    size_t n_rows;      /**< Number of rows */    
    size_t n_cols;      /**< Number of columns */
} df_t;

#endif
