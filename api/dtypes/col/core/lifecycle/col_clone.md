---
title: "col_clone"
description: "Clones the `col_t` instance."
sidebar_position: "3"
tags: [col_clone, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_clone]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
col_t *col_clone(const col_t *col, int *err_out);
```

Clones the `col_t` instance.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`const col_t *col`** ← _Target `col_t` to clone._  
- **`int *err_out`** ← _Optional pointer to receive error codes._  
## Return

- **`col_t *`** → Pointer to the cloned `col_t`. NULL on error.