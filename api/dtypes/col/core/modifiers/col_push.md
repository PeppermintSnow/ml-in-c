---
title: "col_push"
description: "Appends a value to the `col_t`'s data."
sidebar_position: "3"
tags: [col_push, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_push]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
int col_push(col_t *col, const void *val);
```

Appends a value to the `col_t`'s data.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **`const void *val`** ← _Value to append._  
## Return

- **`int`** → Zero on success. Non-zero on error.