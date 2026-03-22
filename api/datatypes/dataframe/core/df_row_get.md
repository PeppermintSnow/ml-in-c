---
title: "df_row_get"
description: "Fetch a target index from a DataFrame."
sidebar_position: "3"
tags: [df_row_get, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_row_get]
last_update:
  date: 2026-02-27
  author: PeppermintSnow
---

```c
double *df_row_get(const dataframe_t *df, const size_t row_idx, int *err_out);
```

Fetch a target index from a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the DataFrame to index._  
- **`const size_t row_idx`** ← _Target row index to fetch._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`double *`** → Array containing values of target row. NULL on error.