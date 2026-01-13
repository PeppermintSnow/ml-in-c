---
title: "DF_fromArray"
description: "Creates a DataFrame with one feature from the given array."
tags: ['core.h', 'Function', 'Added 0.0.0', 'Updated 0.0.0']
keywords: ['ML-in-C', 'machine learning', 'core.h', 'DF_fromArray', 'function DF_fromArray', 'DF_fromArray in core.h']
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
DataFrame *DF_fromArray(double *data, int numRows, char *name);
```

Creates a DataFrame with one feature from the given array.




:::info

Added in version **0.0.0**

:::

## Parameters

- **`double* data`** ← _Pointer to the source array._  
- **`int numRows`** ← _Number of rows/samples in the source array._  
- **`char* name`** ← _Name of the column/feature._  
## Return

- **`DataFrame*`**
**→** _Pointer to the newly created DataFrame._

:::note

- Caller is responsible for freeing allocated memory.

:::

:::tip see also

- [**`DF_free()`**](DF_free) to free the DataFrame.

:::
## Example

```c
#include <ml-in-c/datatypes/dataframe.h>

int main() {
     // Create a DataFrame from an array
     double data[] = {1, 2, 3};
     DataFrame *df = DF_fromArray(data, 3, "feature1");

     return 0;
}
```