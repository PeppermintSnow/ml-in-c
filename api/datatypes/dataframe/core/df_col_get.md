---
title: "df_col_get"
description: "Fetch a target column from a DataFrame."
sidebar_position: "3"
tags: [df_col_get, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_get]
last_update:
  date: 2026-02-27
  author: PeppermintSnow
---

```c
double *df_col_get(const dataframe_t *df, const char *col, int *err_out);
```

Fetch a target column from a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the DataFrame to index._  
- **`const char *col`** ← _Target column to fetch._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double *`** → Array containing values of target column. NULL on error.