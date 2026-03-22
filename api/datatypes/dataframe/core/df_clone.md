---
title: "df_clone"
description: "Creates a copy of a DataFrame."
sidebar_position: "3"
tags: [df_clone, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_clone]
last_update:
  date: 2025-03-12
  author: PeppermintSnow
---

```c
dataframe_t *df_clone(const dataframe_t *df, int *err_out);
```

Creates a copy of a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`dataframe_t *`** → A copy of the target DataFrame.