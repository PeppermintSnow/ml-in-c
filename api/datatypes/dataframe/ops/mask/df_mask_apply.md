---
title: "df_mask_apply"
description: "Applies the given mask on a DataFrame."
sidebar_position: "3"
tags: [df_mask_apply, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_apply]
last_update:
  date: 2025-03-07
  author: PeppermintSnow
---

```c
int df_mask_apply(dataframe_t *df, const df_mask_t *mask);
```

Applies the given mask on a DataFrame.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer to the target DataFrame._  
- **`const df_mask_t *mask`** ← _Pointer to the mask._  
## Return

- **`int`** → 0 on success, non-zero on failure.