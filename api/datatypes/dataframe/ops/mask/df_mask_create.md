---
title: "df_mask_create"
description: "Instantiates a boolean mask of length n_rows."
sidebar_position: "3"
tags: [df_mask_create, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_create]
last_update:
  date: 2025-03-07
  author: PeppermintSnow
---

```c
df_mask_t *df_mask_create(const int n_rows, int *err_out);
```

Instantiates a boolean mask of length n_rows.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const int n_rows`** ← _Row count of target DataFrame._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`df_mask_t *`** → Mask with n_rows initialized to 0xFF.
:::note

- Caller is responsible for freeing allocated memory.

:::

:::tip see also

- [**`df_mask_free()`**](df_mask_free) to free the mask.

:::
