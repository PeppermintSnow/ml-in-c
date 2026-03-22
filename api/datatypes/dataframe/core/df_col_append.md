---
title: "df_col_append"
description: "Adds a single column/feature to an existing DataFrame."
sidebar_position: "3"
tags: [df_col_append, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_append]
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
int df_col_append(dataframe_t *df, const double *data, const size_t n_rows, const char *col);
```

Adds a single column/feature to an existing DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the existing DataFrame to add the column on._  
- **`const double *data`** ← _Pointer to the source array containing the new data to be added._  
- **`const size_t n_rows`** ← _Number of rows in the data to be added._  
- **`const char *col`** ← _Name of the new column._  
## Return

- **`int`** → 0 on success, non-zero on failure.