---
title: "col_string_at"
description: "Accesses a `char *` at the specified index."
sidebar_position: "3"
tags: [col_string_at, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_string_at]
last_update:
  date: 2026-03-27
  author: PeppermintSnow
---

```c
static inline const char *col_string_at(
    const col_t *col,
    const size_t idx,
    int *err_out
    ) {
    if (col-\>dtype != COL_DTYPE_STRING)
return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
```

Accesses a `char *` at the specified index.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const col_t *col`** ← _Target `col_t` to access._  
- **`const size_t idx`** ← _Target index of `col_t` to access._  
- **` err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`static inline const char *`** → Pointer to the `char *` at `col-\>data[idx]`. NULL on error.