---
title: "col_int64_set"
description: "Modifies the value at the specified index. Used for `int64` dtypes."
sidebar_position: "3"
tags: [col_int64_set, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_int64_set]
last_update:
  date: 2026-03-31
  author: PeppermintSnow
---

```c
static inline int col_int64_set(col_t *col, const int64_t val, const size_t idx) {
    if (col-\>dtype != COL_DTYPE_INT64)
return COL_ERR_INVALID_DTYPE;
```

Modifies the value at the specified index. Used for `int64` dtypes.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const int64_t val`** ← _Value to set it to._  
- **` idx`** ← _Target index to modify._  
## Return

- **`static inline int`** → Zero on success. Non-zero on error.