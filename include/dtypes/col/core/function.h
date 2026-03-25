#ifndef COL_CORE_FUNCTION_H
#define COL_CORE_FUNCTION_H

#include "dtypes/col/core/struct.h"
#include "dtypes/col/core/enum.h"

/* lifecycle */

/**
 * @brief Creates a `col_t` from the input parameters.
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
col_t *col_from_array(
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

/* access */ 

/**
 * @brief Access the `col_t`'s data at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index in the col parameter.
 * @param err_out Optional pointer to receive error codes.
 * @return Pointer to a singular value on success. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
void *col_at(const col_t *col, const size_t idx, int *err_out);

/* modification */

/**
 * @brief Modifies the value of `col_t`'s data at the specified index.
 *
 * @param col Target `col_t` to access.
 * @param idx Target index in the col parameter.
 * @param val Value to set at the specified index.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_set(col_t *col, const size_t idx, const void *val);

/**
 * @brief Appends a value to the `col_t`'s data.
 *
 * @param col Target `col_t` to modify.
 * @param val Value to append.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_push(col_t *col, const void *val);

/**
 * @brief Removes the specified index from the `col_t`'s data.
 *
 * @param col Target `col_t` to modify.
 * @param idx Target index to remove in the col parameter.
 * @return Zero on success. Non-zero on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-24
 */
int col_pop(col_t *col, const size_t idx);

#endif
