---
title: "col_dtype_t"
description: "Datatypes for `df_col_t`."
sidebar_position: "2"
tags: [col_dtype_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_dtype_t]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
typedef enum col_dtype {
    COL_DTYPE_DOUBLE = 0,
    COL_DTYPE_FLOAT,
    COL_DTYPE_INT64,
    COL_DTYPE_INT32,
    COL_DTYPE_UINT8,
    COL_DTYPE_STRING
} col_dtype_t;
```

Datatypes for `df_col_t`.



:::info

Last updated in version **0.0.0**

:::

## Members

- **`COL_DTYPE_DOUBLE = 0`** ← _C double (64-bit double-precision float)_  
- **`COL_DTYPE_FLOAT = 1`** ← _C float (32-bit single-precision float)_  
- **`COL_DTYPE_INT64 = 2`** ← _int64_t (64-bit signed integer)_  
- **`COL_DTYPE_INT32 = 3`** ← _int32_t (32-bit signed integer)_  
- **`COL_DTYPE_UINT8 = 4`** ← _uint8_t (8-bit unsigned integer)_  
- **`COL_DTYPE_STRING = 5`** ← _char* (null-terminated string)_  
