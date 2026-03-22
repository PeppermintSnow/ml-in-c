---
title: "df_col_drop"
description: "Deletes the specified column from a DataFrame."
sidebar_position: "3"
tags: [df_col_drop, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_col_drop]
last_update:
  date: 2026-02-20
  author: PeppermintSnow
---

```c
int df_col_drop(dataframe_t *df, const char *col);
```

Deletes the specified column from a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the existing DataFrame to delete the column from._  
- **`const char *col`** ← _Name of the column/feature to be deleted._  
## Return

- **`int`** → 0 on success, non-zero on failure.