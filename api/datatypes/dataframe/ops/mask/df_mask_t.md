---
title: "df_mask_t"
description: "Represents a boolean mask for filtering DataFrames."
sidebar_position: "1"
tags: [df_mask_t, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_mask_t]
last_update:
  date: 2026-03-07
  author: PeppermintSnow
---

```c
typedef struct df_mask {
    uint8_t *data;
    size_t n_rows;
    size_t n_keep;
} df_mask_t;
```

Represents a boolean mask for filtering DataFrames.



:::info

Last updated in version **0.0.0**

:::

## Properties

- **`uint8_t *data`** ← _Boolean array containing 0x00 or 0xFF_  
- **`size_t n_rows;`** ← _Total number of rows, inherited target DataFrame_  
- **`size_t n_keep;`** ← _Number of 0xFF values in data_  
