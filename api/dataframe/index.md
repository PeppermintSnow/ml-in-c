---
title: "DataFrame"
description: "Represents a matrix with names for each column. Data is stored as a row-major flattened array."
keywords: ['DataFrame', 'df', 'matrix', 'array', 'flattened']
last_updated: 2025-09-14
---

```c
typedef struct {
	double *data;
	int numRows;
	int numCols;
	char **featureNames;
} DataFrame;
```

Represents a matrix with names for each column.

Data is stored as a row-major flattened array.

:::note

Added in version **0.0.0**

:::

## Struct Members

- **`double* data`** ← _Flattened array_
- **`int numRows`** ← _Number of rows (samples)_
- **`int numCols`** ← _Number of columns (features) per row_
- **`char** featureNames`** ← _Array of column/feature names_

## Related Functions

- [**`DF_addColumn`**](localhost:3000/ml-in-c/api/dataframe/DF_addColumn) → `int`  
_Adds a single column/feature to an existing DataFrame._  
**Params**: `DataFrame *df` `double *data` `char *name`
- [**`DF_free`**](localhost:3000/ml-in-c/api/dataframe/DF_free) → `void`  
_Frees all allocated memory by the DataFrame._  
**Params**: `DataFrame *df`
- [**`DF_fromArray`**](localhost:3000/ml-in-c/api/dataframe/DF_fromArray) → `DataFrame`  
_Creates a DataFrame with one feature from the given array._  
**Params**: `double *data` `int numRows` `char *name`
