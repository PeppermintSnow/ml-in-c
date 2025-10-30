---
title: "DataFrame"
description: "Represents a matrix with names for each column. Data is stored as a row-major flattened array."
tags: ['dataframe.h', 'Struct', 'Added 0.0.0', 'Updated 0.0.0']
keywords: ['ML-in-C', 'machine learning', 'dataframe.h', 'DataFrame', 'struct DataFrame', 'DataFrame in dataframe.h']
last_update:
  date: 2025-09-14
  author: PeppermintSnow
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


:::info

Added in version **0.0.0**

:::

## Struct Members

- **`double* data`** ← _Flattened array_
- **`int numRows`** ← _Number of rows (samples)_
- **`int numCols`** ← _Number of columns (features) per row_
- **`char** featureNames`** ← _Array of column/feature names_

## Related Functions
- [**`DF_addColumn`**](DF_addColumn) → `int`  
_Adds a single column/feature to an existing DataFrame._  
**Params**: `DataFrame* df`  `double* data`  `char* name` 

- [**`DF_free`**](DF_free) → `void`  
_Frees all allocated memory by the DataFrame._  
**Params**: `DataFrame* df` 

- [**`DF_fromArray`**](DF_fromArray) → `DataFrame*`  
_Creates a DataFrame with one feature from the given array._  
**Params**: `double* data`  `int numRows`  `char* name` 

## Example

```c
#include <ml-in-c/datatypes/dataframe.h>

int main() {
     // Create from array
     double data[] = {1, 2, 3};
     DataFrame *df = DF_fromArray(data, 3, "feature1");

     // Add a column
     double newData[] = {4, 5, 6};
     DF_addColumn(df, newData, "feature2");

     // Free array from memory
     DF_free(df);

     return 0;
}
```