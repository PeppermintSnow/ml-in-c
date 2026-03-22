---
title: "df_col_mul_s"
description: "Multiplies the scalar value with each row of the target column."
sidebar_position: "3"
tags: [df_col_mul_s, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_mul_s]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
double *df_col_mul_s(
    const dataframe_t *df,
    const char *col,
    const double scalar,
    int *err_out
);
```

Multiplies the scalar value with each row of the target column.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col`** ← _Name of the target column._  
- **`const double scalar`** ← _Scalar value to multiply each row of the column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double *`** → Array of products. NULL on error.