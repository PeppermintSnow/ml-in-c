---
title: "Core Functions"
---

- [**`DF_addColumn`**](DF_addColumn) → `int`  
_Adds a single column/feature to an existing DataFrame._  
**Params**: `DataFrame* df`  `double* data`  `char* name` 

- [**`DF_free`**](DF_free) → `void`  
_Frees all allocated memory by the DataFrame._  
**Params**: `DataFrame* df` 

- [**`DF_fromArray`**](DF_fromArray) → `DataFrame*`  
_Creates a DataFrame with one feature from the given array._  
**Params**: `double* data`  `int numRows`  `char* name` 
