---
title: "df_mask_comparison_t"
description: "Comparison enumerables for DataFrame masking functions."
sidebar_position: "2"
tags: [df_mask_comparison_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_comparison_t]
last_update:
  date: 2026-03-07
  author: PeppermintSnow
---

```c
typedef enum {
    DF_MASK_EQ = 0,
    DF_MASK_NE,
    DF_MASK_LT,
    DF_MASK_GT,
    DF_MASK_LE,
    DF_MASK_GE
} df_mask_comparison_t;
```

Comparison enumerables for DataFrame masking functions.



:::info

Last updated in version **0.0.0**

:::

## Members

- **`DF_MASK_EQ = 0`** ← _Equal to (==)_  
- **`DF_MASK_NE = 1`** ← _Not equal to (!=)_  
- **`DF_MASK_LT = 2`** ← _Less than (\<)_  
- **`DF_MASK_GT = 3`** ← _Greater than (\>)_  
- **`DF_MASK_LE = 4`** ← _Less than or equal to (\<=)_  
- **`DF_MASK_GE = 5`** ← _Greater than or equal to (\>=)_  

:::tip see also

- [**`df_mask_or()`**](df_mask_or) for use with logical OR filtering.
- [**`df_mask_and()`**](df_mask_and) for use with logical AND filtering.

:::
