---
title: "df_row_append"
description: "Adds a row/entry to a DataFrame."
sidebar_position: "3"
tags: [df_row_append, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_row_append]
last_update:
  date: 2026-02-20
  author: PeppermintSnow
---

```c
int df_row_append(dataframe_t *df, const double *data, const size_t n_columns);
```

Adds a row/entry to a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the existing DataFrame to add the row to._  
- **`const double *data`** ← _Pointer to the source array containing the new data to be added._  
- **`const size_t n_columns`** ← _Number of column in the data to be added._  
## Return

- **`int`** → 0 on success, non-zero on failure.