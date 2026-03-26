#ifndef COL_CORE_MODIFIERS_H
#define COL_CORE_MODIFIERS_H

#include "dtypes/col/core/type.h"

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
