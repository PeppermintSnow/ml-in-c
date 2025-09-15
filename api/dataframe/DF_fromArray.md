---
title: "DF_fromArray"
description: "Creates a DataFrame with one feature from the given array"
keywords: ['DataFrame', 'df', 'matrix', 'array', 'flattened']
last_updated: 2025-09-14
---

```c
DataFrame *DF_fromArray(double *data, int numRows, char *name);
```

Creates a DataFrame with one feature from the given array

:::note

Added in version **0.0.0**

:::

## Parameters

- **`double* data`** ← _Pointer to the source array._
- **`int numRows`** ← _Number of rows/samples in the source array._
- **`char* name`** ← _Name of the column/feature._

## Returns

- **`DataFrame*`**  → _Pointer to the newly created DataFrame._

:::note

Caller is responsible for freeing allocated memory.

:::

:::tip[**SEE ALSO**]

- [**`DF_free()`**](localhost:3000/ml-in-c/api/dataframe/DF_free) to free the DataFrame.
:::

