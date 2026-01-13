---
title: "DF_addColumn"
description: "Adds a single column/feature to an existing DataFrame."
tags: ['core.h', 'Function', 'Added 0.0.0', 'Updated 0.0.0']
keywords: ['ML-in-C', 'machine learning', 'core.h', 'DF_addColumn', 'function DF_addColumn', 'DF_addColumn in core.h']
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
int DF_addColumn(DataFrame *df, double *data, char *name);
```

Adds a single column/feature to an existing DataFrame.




:::info

Added in version **0.0.0**

:::

## Parameters

- **`DataFrame* df`** ← _Pointer to the existing DataFrame to add the column on._  
- **`double* data`** ← _Pointer to the source array containing the new data to be added._  
- **`char* name`** ← _Name of the new column/feature._  
## Return

- **`int`**
**→** _0 on success, non-zero on failure._
## Example

```c
#include <ml-in-c/datatypes/dataframe.h>

int main() {
     // Create a DataFrame from an array
     double data[] = {1, 2, 3};
     DataFrame *df = DF_fromArray(data, 3, "feature1");
     
     // Add a column to the existing DataFrame
     double newData[] = {4, 5, 6};
     DF_addColumn(df, newData, "feature2");

     return 0;
}
 
```