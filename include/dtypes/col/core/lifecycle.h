#ifndef COL_CORE_LIFECYCLE_H
#define COL_CORE_LIFECYCLE_H

#include "dtypes/col/core/type.h"

/**
 * @brief Creates an empty `col_t`.
 *
 * @param name Name of the column.
 * @param data Array of column elements.
 * @param n_rows Number of rows in the data parameter.
 * @param dtype Datatype of the column.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the newly created `col_t`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-26
 */
col_t *col_create(
    const char *name,
    const col_dtype_t dtype,
    int *err_out
);

/**
 * @brief Creates a `col_t` initialized from an array.
 *
 * @param name Name of the column.
 * @param data Array of column elements.
 * @param n_rows Number of rows in the data parameter.
 * @param dtype Datatype of the column.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the newly created `col_t`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
col_t *col_create_array(
    const char *name,
    const void *data, 
    const size_t n_rows, 
    const col_dtype_t dtype,
    int *err_out
);

/**
 * @brief Clones the `col_t` instance.
 *
 * @param col Target `col_t` to clone.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to the cloned `col_t`. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
col_t *col_clone(const col_t *col, int *err_out);

/**
 * @brief Frees the `col_t` instance and its properties from memory.
 *
 * @param col Target `col_t` to free.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_free(col_t *col);

#endif
