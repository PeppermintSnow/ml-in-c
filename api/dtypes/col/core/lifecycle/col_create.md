---
title: "col_create"
description: "Creates an empty `col_t`."
sidebar_position: "3"
tags: [col_create, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_create]
last_update:
  date: 2026-03-26
  author: PeppermintSnow
---

```c
col_t *col_create(
    const char *name,
    const col_dtype_t dtype,
    int *err_out
);
```

Creates an empty `col_t`.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const char *name`** ← _Name of the column._  
- **` data`** ← _Array of column elements._  
- **` n_rows`** ← _Number of rows in the data parameter._  
- **` dtype`** ← _Datatype of the column._  
- **` err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`col_t *`** → Pointer to the newly created `col_t`. NULL on error.