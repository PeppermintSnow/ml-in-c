---
title: "df_from_array"
description: "Creates a DataFrame with one feature from the given array."
sidebar_position: "3"
tags: [df_from_array, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_from_array]
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
dataframe_t *df_from_array(
    const double *data,
    const size_t n_rows,
    const char *col,
    int *err_out
);
```

Creates a DataFrame with one feature from the given array.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const double *data`** ← _Pointer to the source array._  
- **`const size_t n_rows`** ← _Number of rows/samples in the source array._  
- **`const char *col`** ← _Name of the column._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`dataframe_t *`** → Pointer to the newly created DataFrame. NULL on error.
:::note

- Caller is responsible for freeing allocated memory.

:::

:::tip see also

- [**`df_free()`**](df_free) to free the DataFrame.

:::
