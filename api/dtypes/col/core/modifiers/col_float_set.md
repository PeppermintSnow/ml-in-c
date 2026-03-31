---
title: "col_float_set"
description: "Modifies the value at the specified index. Used for `float` dtypes."
sidebar_position: "3"
tags: [col_float_set, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_float_set]
last_update:
  date: 2026-03-31
  author: PeppermintSnow
---

```c
static inline int col_float_set(col_t *col, const float val, const size_t idx) {
    if (col-\>dtype != COL_DTYPE_FLOAT)
return COL_ERR_INVALID_DTYPE;
```

Modifies the value at the specified index. Used for `float` dtypes.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const float val`** ← _Value to set it to._  
- **` idx`** ← _Target index to modify._  
## Return

- **`static inline int`** → Zero on success. Non-zero on error.