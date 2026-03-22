---
title: "df_mask_and"
description: "Applies an AND gate to the current mask data."
sidebar_position: "3"
tags: [df_mask_and, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_and]
last_update:
  date: 2025-03-07
  author: PeppermintSnow
---

```c
int df_mask_and(
    df_mask_t *mask,
    const dataframe_t *df,
    const char *col,
    const df_mask_comparison_t comp,
    const double value
);
```

Applies an AND gate to the current mask data.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`df_mask_t *mask`** ← _Pointer to existing mask that will be modified._  
- **`const dataframe_t *df`** ← _Pointer to DataFrame containing the data to compare._  
- **`const char *col`** ← _Name of the column in the DataFrame._  
- **`const df_mask_comparison_t comp`** ← _Comparison operator enumerable. (e.g., DF_MASK_EQUAL)._  
- **`const double value`** ← _Value to be compared against._  
## Return

- **`int`** → 0 on success, non-zero on failure.
:::tip see also

- [**`df_mask_comparison_t`**](df_mask_comparison_t) for valid comparison parameters.

:::
