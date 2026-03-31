---
title: "col_int64_get"
description: "Returns a read-only `int64_t *` data."
sidebar_position: "3"
tags: [col_int64_get, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_int64_get]
last_update:
  date: 2026-03-27
  author: PeppermintSnow
---

```c
static inline const int64_t *col_int64_get(const col_t *col, int *err_out) {
    if (col-\>dtype != COL_DTYPE_INT64)
return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
```

Returns a read-only `int64_t *` data.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const col_t *col`** ← _Target `col_t` to access._  
- **` err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`static inline const int64_t *`** → Typecasted `int64_t *` pointer to `col-\>data`. NULL on error.