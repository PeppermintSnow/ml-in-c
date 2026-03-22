---
title: "df_col_select"
description: "Keeps only the specified columns in the DataFrame."
sidebar_position: "3"
tags: [df_col_select, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_select]
last_update:
  date: 2025-03-12
  author: PeppermintSnow
---

```c
int df_col_select(dataframe_t *df, const char **cols, const size_t n_cols);
```

Keeps only the specified columns in the DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char **cols`** ← _Array of column names to keep._  
- **`const size_t n_cols`** ← _Length of the `cols` parameter._  
## Return

- **`int`** → 0 on success, non-zero on failure.