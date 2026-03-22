---
title: "df_row_select"
description: "Keeps only the range of rows in the DataFrame."
sidebar_position: "3"
tags: [df_row_select, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_row_select]
last_update:
  date: 2025-03-12
  author: PeppermintSnow
---

```c
int df_row_select(dataframe_t *df, const size_t start, const size_t end);
```

Keeps only the range of rows in the DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const size_t start`** ← _Index to slice from._  
- **`const size_t end`** ← _Index to slice to._  
## Return

- **`int`** → 0 on success, non-zero on failure.