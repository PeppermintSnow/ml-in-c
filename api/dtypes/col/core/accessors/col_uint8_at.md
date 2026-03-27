---
title: "col_uint8_at"
description: "Accesses an `uint8_t` at the specified index."
sidebar_position: "3"
tags: [col_uint8_at, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_uint8_at]
last_update:
  date: 2026-03-27
  author: PeppermintSnow
---

```c
static inline const uint8_t *col_uint8_at(
    const col_t *col,
    const size_t idx,
    int *err_out
    ) {
    if (col-\>dtype != COL_DTYPE_UINT8)
return mlc_fail_null(COL_ERR_INVALID_DTYPE, err_out);
```

Accesses an `uint8_t` at the specified index.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const col_t *col`** ← _Target `col_t` to access._  
- **`const size_t idx`** ← _Target index of `col_t` to access._  
- **` err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`static inline const uint8_t *`** → Pointer to the `uint8_t` at `col-\>data[idx]`. NULL on error.