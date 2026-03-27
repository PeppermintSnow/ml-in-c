---
title: "col_create_array"
description: "Creates a `col_t` initialized from an array."
sidebar_position: "3"
tags: [col_create_array, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_create_array]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
col_t *col_create_array(
    const char *name,
    const void *data,
    const size_t n_rows,
    const col_dtype_t dtype,
    int *err_out
);
```

Creates a `col_t` initialized from an array.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const char *name`** ← _Name of the column._  
- **`const void *data`** ← _Array of column elements._  
- **`const size_t n_rows`** ← _Number of rows in the data parameter._  
- **`const col_dtype_t dtype`** ← _Datatype of the column._  
- **`int *err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`col_t *`** → Pointer to the newly created `col_t`. NULL on error.