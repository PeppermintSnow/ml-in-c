---
title: "col_t"
description: "Represents a column containing an array of data in a dataframe."
sidebar_position: "1"
tags: [col_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_t]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
typedef struct col {
    char *name;
    void *data;
    size_t n_rows;
    const col_dtype_t dtype;
    const size_t stride;
} col_t;
```

Represents a column containing an array of data in a dataframe.



:::info

Last updated in version **0.0.0**

:::

## Properties

- **`char *nam`** ← _Name of the column_  
- **`void *dat`** ← _Array of data in the column_  
- **`size_t n_rows`** ← _Number of rows_  
- **`const col_dtype_t dtype`** ← _Datatype  of the column_  
- **`const size_t stride`** ← _Byte offset of the datatype_  
