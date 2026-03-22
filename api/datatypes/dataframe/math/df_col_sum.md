---
title: "df_col_sum"
description: "Computes the sum of the target column."
sidebar_position: "3"
tags: [df_col_sum, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_sum]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
double df_col_sum(
    const dataframe_t *df,
    const char *col,
    int *err_out
);
```

Computes the sum of the target column.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col`** ← _Name of the target column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double`** → Sum of all rows. NAN on error.