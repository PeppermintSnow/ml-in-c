---
title: "DF_addColumn"
description: "Adds a single column/feature to an existing DataFrame"
keywords: ['DataFrame', 'df', 'matrix', 'array', 'flattened']
last_updated: 2025-09-14
---

```c
int DF_addColumn(DataFrame *df, double *data, char *name);
```

Adds a single column/feature to an existing DataFrame

:::note

Added in version **0.0.0**

:::

## Parameters

- **`DataFrame* df`** ← _Pointer to the existing DataFrame to add the column on._
- **`double* data`** ← _Pointer to the source array containing the new data to be added._
- **`char* name`** ← _Name of the new column/feature._

## Returns

- **`int`**  → _0 on success, non-zero on failure._

