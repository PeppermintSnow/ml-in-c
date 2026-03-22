---
title: "df_col_add"
description: "Performs row-wise addition of col1 to col2."
sidebar_position: "3"
tags: [df_col_add, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_add]
last_update:
  date: 2026-02-28
  author: PeppermintSnow
---

```c
double *df_col_add(
    const dataframe_t *df,
    const char *col1,
    const char *col2,
    int *err_out
);
```

Performs row-wise addition of col1 to col2.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col1`** ← _Name of the first addend column._  
- **`const char *col2`** ← _Name of the second addend column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double *`** → Array of sums. NULL on error.