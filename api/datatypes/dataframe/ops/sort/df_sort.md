---
title: "df_sort"
description: "Sorts the DataFrame by specified columns in sequential order."
sidebar_position: "3"
tags: [df_sort, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_sort]
last_update:
  date: 2025-03-21
  author: PeppermintSnow
---

```c
int df_sort(
    dataframe_t *df,
    const char *col,
    const df_sort_order order
);
```

Sorts the DataFrame by specified columns in sequential order.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const char *col`** ← _Column name to sort by._  
- **`const df_sort_order order`** ← _Sorting order_  
## Return

- **`int`** → 0 on success, non-zero on failure.
:::tip see also

- [**`df_sort_order`**](df_sort_order) for a list of valid sorting order enumerables.

:::
