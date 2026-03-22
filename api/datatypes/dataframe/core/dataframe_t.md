---
title: "dataframe_t"
description: "Represents a matrix with names for each column. Data is stored as a row-major flattened array."
sidebar_position: "1"
tags: [dataframe_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, dataframe_t]
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
typedef struct dataframe {
    double *data;
    char **columns;
    size_t n_rows;
    size_t n_cols;
} dataframe_t;
```

Represents a matrix with names for each column.

Data is stored as a row-major flattened array.

:::info

Last updated in version **0.0.0**

:::

## Properties

- **`double *data`** ← _Flattened array_  
- **`char **columns`** ← _Array of column names_  
- **`size_t n_rows;`** ← _Number of rows_  
- **`size_t n_cols;`** ← _Number of columns_  
