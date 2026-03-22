---
title: "df_row_drop"
description: "Deletes a row/entry from a DataFrame."
sidebar_position: "3"
tags: [df_row_drop, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_row_drop]
last_update:
  date: 2026-02-20
  author: PeppermintSnow
---

```c
int df_row_drop(dataframe_t *df, const size_t row_idx);
```

Deletes a row/entry from a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the existing DataFrame to remove the row from._  
- **`const size_t row_idx`** ← _Index of the row to be deleted._  
## Return

- **`int`** → 0 on success, non-zero on failure.