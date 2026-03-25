#ifndef DATAFRAME_MASK_INTERNAL_H
#define DATAFRAME_MASK_INTERNAL_H

#include "./mask.h"

static inline uint8_t apply_condition(
    const double data, 
    const double val, 
    const df_mask_comparison_t op
) {
    switch (op) {
        case DF_MASK_EQ: return (data == val) ? 0xFF : 0x00;
        case DF_MASK_NE: return (data != val) ? 0xFF : 0x00;
        case DF_MASK_LT: return (data < val) ? 0xFF : 0x00;
        case DF_MASK_LE: return (data <= val) ? 0xFF : 0x00;
        case DF_MASK_GT: return (data > val) ? 0xFF : 0x00;
        case DF_MASK_GE: return (data >= val) ? 0xFF : 0x00;
    }   
    return 0x00;
}

#endif
