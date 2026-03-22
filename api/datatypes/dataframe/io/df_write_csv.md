---
title: "df_write_csv"
description: "Instantiates a DataFrame containing data from a CSV file."
sidebar_position: "3"
tags: [df_write_csv, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_write_csv]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
int df_write_csv(dataframe_t *df, char *path, int precision);
```

Instantiates a DataFrame containing data from a CSV file.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`dataframe_t *df`** ← _Pointer of the DataFrame to save._  
- **`char *path`** ← _Path of which to save the CSV file to._  
- **`int precision`** ← _Floating point precision of the data._  
## Return

- **`int`** → 0 on success, non-zero on failure.