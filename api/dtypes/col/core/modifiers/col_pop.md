---
title: "col_pop"
description: "Removes the specified index from the `col_t`'s data."
sidebar_position: "3"
tags: [col_pop, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_pop]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
int col_pop(col_t *col, const size_t idx);
```

Removes the specified index from the `col_t`'s data.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const size_t idx`** ← _Target index to remove in the col parameter._  
## Return

- **`int`** → Zero on success. Non-zero on error.