---
title: "df_col_var"
description: "Computes the population variance of the target column."
sidebar_position: "3"
tags: [df_col_var, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_var]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
double df_col_var(
    const dataframe_t *df,
    const char *col,
    int *err_out
);
```

Computes the population variance of the target column.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col`** ← _Name of the target column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double`** → Population variance. NAN on error.