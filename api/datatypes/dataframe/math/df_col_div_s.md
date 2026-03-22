---
title: "df_col_div_s"
description: "Divides each row of the target column by the scalar value."
sidebar_position: "3"
tags: [df_col_div_s, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_div_s]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
double *df_col_div_s(
    const dataframe_t *df,
    const char *col,
    const double scalar,
    int *err_out
);
```

Divides each row of the target column by the scalar value.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col`** ← _Name of the target column._  
- **`const double scalar`** ← _Scalar value to divide each row of the column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double *`** → Array of quotients. NULL on error.