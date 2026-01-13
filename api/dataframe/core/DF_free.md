---
title: "DF_free"
description: "Frees all allocated memory by the DataFrame."
tags: ['core.h', 'Function', 'Added 0.0.0', 'Updated 0.0.0']
keywords: ['ML-in-C', 'machine learning', 'core.h', 'DF_free', 'function DF_free', 'DF_free in core.h']
last_update:
  date: 2025-09-14
  author: PeppermintSnow
---

```c
void DF_free(DataFrame *df);
```

Frees all allocated memory by the DataFrame.




:::info

Added in version **0.0.0**

:::

## Parameters

- **`DataFrame* df`** ← _Pointer to the DataFrame to free._  
## Return

- **`void`**

## Example

```c
#include <ml-in-c/datatypes/dataframe.h>

int main() {
     // Create a DataFrame from an array
     double data[] = {1, 2, 3};
     DataFrame *df = DF_fromArray(data, 3, "feature1");
     
     // Free DataFrame from allocated memory
     DF_free(df);

     return 0;
}
 
```