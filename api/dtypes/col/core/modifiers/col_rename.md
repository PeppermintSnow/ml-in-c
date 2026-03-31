---
title: "col_rename"
description: "Renames a `col_t`'s `name` property."
sidebar_position: "3"
tags: [col_rename, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, col_rename]
last_update:
  date: 2026-03-24
  author: PeppermintSnow
---

```c
int col_rename(col_t *col, const char *name);
```

Renames a `col_t`'s `name` property.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`col_t *col`** ← _Target `col_t` to modify._  
- **` idx`** ← _Target index to remove in the col parameter._  
## Return

- **`int`** → Zero on success. Non-zero on error.