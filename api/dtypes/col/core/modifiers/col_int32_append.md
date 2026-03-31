---
title: "col_int32_append"
description: "Appends a value to the `col_t`'s data. Used for `int32` dtypes."
sidebar_position: "3"
tags: [col_int32_append, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_int32_append]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
static inline int col_int32_append(col_t *col, const int32_t val) {
    if (col-\>dtype != COL_DTYPE_INT32)
return COL_ERR_INVALID_DTYPE;
```

Appends a value to the `col_t`'s data. Used for `int32` dtypes.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **` val`** ← _Value to append._  
## Return

- **`static inline int`** → Zero on success. Non-zero on error.