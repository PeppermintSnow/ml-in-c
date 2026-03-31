---
title: "col_string_append"
description: "Appends a value to the `col_t`'s data. Used for `string` dtypes."
sidebar_position: "3"
tags: [col_string_append, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_string_append]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
static inline int col_string_append(col_t *col, const char *val) {
    if (col-\>dtype != COL_DTYPE_STRING)
return COL_ERR_INVALID_DTYPE;
```

Appends a value to the `col_t`'s data. Used for `string` dtypes.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **` val`** ← _Value to append._  
## Return

- **`static inline int`** → Zero on success. Non-zero on error.