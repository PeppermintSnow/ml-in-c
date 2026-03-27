---
title: "col_free"
description: "Frees the `col_t` instance and its properties from memory."
sidebar_position: "3"
tags: [col_free, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_free]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
int col_free(col_t *col);
```

Frees the `col_t` instance and its properties from memory.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to free._  
## Return

- **`int`** → Zero on success. Non-zero on error.