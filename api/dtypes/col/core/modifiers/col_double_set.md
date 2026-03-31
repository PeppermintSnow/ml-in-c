---
title: "col_double_set"
description: "Modifies the value at the specified index. Used for `double` dtypes."
sidebar_position: "3"
tags: [col_double_set, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_double_set]
last_update:
  date: 2026-03-31
  author: PeppermintSnow
---

```c
static inline int col_double_set(col_t *col, const double val, const size_t idx) {
    if (col-\>dtype != COL_DTYPE_DOUBLE)
return COL_ERR_INVALID_DTYPE;
```

Modifies the value at the specified index. Used for `double` dtypes.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const double val`** ← _Value to set it to._  
- **` idx`** ← _Target index to modify._  
## Return

- **`static inline int`** → Zero on success. Non-zero on error.