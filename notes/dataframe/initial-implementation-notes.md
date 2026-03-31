---
title: "Initial Implementation Notes"
description: "Initial design and implementation notes for the dataframe_t type."
sidebar_position: 1
last_updated:
    date: 2026-03-22
    author: PeppermintSnow
---

# DataFrame Implementation

## Overview

The [**`dataframe_t`**][df_t] is **ML-in-C**'s core datatype, which is designed to drive most machine learning operations. It uses a row-major flattened array to store data, but can be represented as a 2D array or a matrix by utilizing its `n_rows` and `n_cols` struct properties. The initial implementation features minimal suite of helper functions to aid the user in data manipulation tasks. However, one glaring limitation is that its data is fixed to the `double` datatype, meaning string operations are not supported as of writing. Moreover, missing values or NaNs are not handled as of yet, which could result in a corrupted dataframe if a dataset with mismatched rows/columns or missing data is used.

## Major Design Choices

### Data Manipulation

While the library supports essential row/column operations such as appending, dropping, slicing, sorting, and masking, they are made intentionally lightweight. The primary focus of the library is the machine learning workflow, hence, extensive data manipulation features were not a priority in the initial implementation.

### Memory Layout

While the [**`dataframe_t`**][df_t] represents a matrix, it stores its data as a row-major one-dimensional array, taking inspiration from **numpy**'s [**`ndarray`**][np] design. While not ideal for data manipulation tasks, it provides benefits in machine learning workflows; this is in line with model training, which often iterates through rows multiple times.

Data access is done by strides, utilizing the [**`dataframe_t`**][df_t]'s `n_rows` and `n_cols` properties. Accessing a column in a row can be done by using the following formula:

$$r_ic_j = r_{i} \cdot \text{n\_cols} + c_j $$

<p style={{marginBottom:0}}>Where:</p>
- $r_i$ is the target row index;
- $c_j$ is the target column index;
- and $\text{n\_cols}$ is the total number of columns.

Although sub-optimal for columnar operations, this contiguous row-major format groups entire rows together as blocks. This allows for efficient `memcpy` operations when accessing/cloning rows, avoiding the overhead of iterating column by column.

### Byte Masking 

A separate struct called [**`df_mask_t`**][mask_t] was made, bundled with its helper functions to perform logical AND and OR operations on the filtering conditions. Under the hood, it stores a corresponding `uint8_t` for each row index. The `uint8_t` datatype was chosen for memory efficiency as it is guaranteed to occupy only 1 byte of memory, unlike `<stdbool.h>`'s `bool` implementation-specific size variations.

Unlike [**pandas' boolean mask**][pd_mask], the [**`df_mask_t`**][mask_t] performs byte masking, and is set to two possible values: `0x00` and `0xFF`. Initially, all values of the mask is set to `0xFF`. The user may modify this by using the logical `AND` and `OR` helper functions to apply conditions accordingly.

Byte masking was preferred over boolean masking because it allows bitwise operations, provides memory predictability, and more options for future optimizations.

### Sorting Algorithm

An iterative variant of the [**Lomuto Quick Sort**][lomuto] was chosen as the sorting algorithm. While iteration makes it slightly harder to understand compared to recursion, it helps with predictability, performance, and avoidance of errors. 

[**Lomuto partitioning**][lomuto] partitions the array and picks the last element as the pivot. While slower than other partitioning algorithms, it is arguably the simplest. Sorting is not expected to be frequently used as this library is focused on the machine learning workflow, which is why a simple algorithm was preferred despite its tradeoffs. Moreover, optimization for the sorting functionality is planned but not prioritized for future updates.

[**Quick Sort**][qsort] was the algorithm of choice due to its in-place design, meaning it does not require an additional array for sorting. It uses $O(\log{n})$ extra memory and $O(n \log{n})$ time complexity on average. 

Datasets may get large in practice, which is why the memory-efficient [**Quick Sort**][qsort] was preferred over the stable [**Merge Sort**][msort].

One noticeable limitation in the current implementation is the lack of tie-breakers. In other words, the dataframe may only be sorted by one key at a time, unlike [**SQL's `ORDER BY`**][sql_order] keyword, which allows for multiple key sorting. Again, sorting is not expected to be frequently used, hence, this feature is not prioritized.

[df_t]: #
[mask_t]: #
[np]: https://numpy.org/doc/2.4/reference/arrays.ndarray.html
[lomuto]: https://www.geeksforgeeks.org/dsa/lomuto-partition-algorithm/
[pd_mask]: https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.mask.html
[qsort]: https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-quick-sort/
[msort]: https://www.geeksforgeeks.org/dsa/merge-sort/
[sql_order]: https://www.w3schools.com/sql/sql_orderby.asp
