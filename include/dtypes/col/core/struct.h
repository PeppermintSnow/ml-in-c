#ifndef COL_CORE_STRUCT_H
#define COL_CORE_STRUCT_H

#include <stddef.h>
#include "dtypes/col/core/enum.h"

/**
 * @brief Represents a column containing an array of data in a dataframe.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
typedef struct col {
    char *name;             /**< Name of the column*/
    void *data;             /**< Array of data in the column*/
    size_t n_rows;          /**< Number of rows*/
    col_dtype_t dtype;    /**< Datatype  of the column*/
} col_t;

#endif
