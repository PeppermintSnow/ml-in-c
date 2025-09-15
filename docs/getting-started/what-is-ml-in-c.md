---
title: "What is ML-in-C?"
description: "An experimental machine learning library written in pure C."
sidebar_position: 1
last_updated:
    date: 2025-09-15
    author: PeppermintSnow
---

**ML-in-C** is a machine learning library written entirely in **pure C**. It aims to provide a complete machine learning toolkit with a primary focus on **performance**, **low-level understanding**, and **experimental development**. 

The library introduces a foundational datatype called [**`DataFrame`**](/api/dataframe), which takes inspiration from the functionality of [**`Pandas' DataFrame`**](https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.html#pandas.DataFrame) while having similar performance and structure to [**`NumPy's ndarray`**](https://numpy.org/doc/stable/reference/generated/numpy.ndarray.html#numpy.ndarray) implemented in C. Differing from most object-oriented machine learning workflows, ML-in-C follows a procedural paradigm as it is the C language's native style. 

## Why does this library exist?

ML-in-C was created as a personal learning project. It exists as an experimental playground to explore, implement, and optimize machine learning algorithms from scratch. 

:::warning

Please note that **ML-in-C is not intended for production or commercial use**!

:::

Instead, this library is designed for:

- Gaining a deeper understanding of machine learning algorithms
- Practicing systems-level development in C
- Experimenting with memory layout, performance, and control

If you are curious about how machine learning libraries work, ML-in-C offers an environment open to experimentation.
