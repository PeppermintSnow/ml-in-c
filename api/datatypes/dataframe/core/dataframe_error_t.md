---
title: "dataframe_error_t"
description: "Error codes for the DataFrame helper functions."
sidebar_position: "2"
tags: [dataframe_error_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, dataframe_error_t]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
typedef enum {
    DF_OK = 0,
    DF_COL_EXISTS,
    DF_NO_COL,
    DF_NO_ROW,
    DF_LAST_COL,
    DF_LAST_ROW,
    DF_ROW_MISMATCH,
    DF_COL_MISMATCH,
    DF_IO,
    DF_OOM,
    DF_BAD_ARG
} dataframe_error_t;
```

Error codes for the DataFrame helper functions.



:::info

Last updated in version **0.0.0**

:::

## Members

- **`DF_OK = 0`** ← _No errors_  
- **`DF_COL_EXISTS = 1`** ← _Column already exists_  
- **`DF_NO_COL = 2`** ← _Column not found_  
- **`DF_NO_ROW = 3`** ← _Row not found_  
- **`DF_LAST_COL = 4`** ← _Cannot delete last column_  
- **`DF_LAST_ROW = 5`** ← _Cannot delete last row_  
- **`DF_ROW_MISMATCH = 6`** ← _Data length does not match df-\>n_rows_  
- **`DF_COL_MISMATCH = 7`** ← _Data length does not match df-\>n_columns_  
- **`DF_IO = 8`** ← _I/O error_  
- **`DF_OOM = 9`** ← _Out of memory_  
- **`DF_BAD_ARG = 10`** ← _Bad argument_  

:::tip see also

- [**`df_strerr()`**](df_strerr) to convert the error codes to messages.

:::
