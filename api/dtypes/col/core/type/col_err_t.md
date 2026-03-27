---
title: "col_err_t"
description: "Error codes for `column_t` helper functions."
sidebar_position: "2"
tags: [col_err_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_err_t]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
typedef enum col_err {
    COL_ERR_OK = 0,
    COL_ERR_IO,
    COL_ERR_OOM,
    COL_ERR_NO_DATA,
    COL_ERR_OUT_OF_BOUNDS,
    COL_ERR_INVALID_DTYPE,
    COL_ERR_EMPTY_NAME,
    COL_ERR_NOT_FOUND,
} col_err_t;
```

Error codes for `column_t` helper functions.



:::info

Last updated in version **0.0.0**

:::

## Members

- **`COL_ERR_OK = 0`** ← _No errors_  
