---
title: "df_read_csv"
description: "Instantiates a DataFrame containing data from a CSV file."
sidebar_position: "3"
tags: [df_read_csv, added 0.0.0, updated 0.0.0]
keywords: [ml-in-c, machine learning, df_read_csv]
last_update:
  date: 2026-03-01
  author: PeppermintSnow
---

```c
dataframe_t *df_read_csv(char *path, int *err_out);
```

Instantiates a DataFrame containing data from a CSV file.



:::info

Last updated in version **0.0.0**

:::

## Parameters

- **`char *path`** ← _Path to CSV file._  
- **`int *err_out`** ← _Optional pointer to receive the error code._  
## Return

- **`dataframe_t *`** → DataFrame with data from the CSV. NULL on error.