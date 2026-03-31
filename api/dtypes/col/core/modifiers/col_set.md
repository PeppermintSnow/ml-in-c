---
title: "col_set"
description: "Modifies the value at the specified index. This serves as a generic setter for internal use. Use the type-safe setters instead."
sidebar_position: "3"
tags: [col_set, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_set]
last_update:
  date: 2026-03-29
  author: PeppermintSnow
---

```c
int col_set(col_t *col, const void *val, const size_t idx);
```

Modifies the value at the specified index.

This serves as a generic setter for internal use. Use the type-safe setters instead.

:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const void *val`** ← _Value to set it to._  
- **`const size_t idx`** ← _Target index to modify._  
## Return

- **`int`** → Zero on success. Non-zero on error.