---
title: "df_mask_free"
description: "Frees all allocated memory by the mask."
sidebar_position: "3"
tags: [df_mask_free, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_free]
last_update:
  date: 2025-03-07
  author: PeppermintSnow
---

```c
int df_mask_free(df_mask_t *mask);
```

Frees all allocated memory by the mask.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`df_mask_t *mask`** ← _Pointer to the mask to free._  
## Return

- **`int`** → 0 on success, non-zero on failure.