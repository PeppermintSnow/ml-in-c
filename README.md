![banner](https://github.com/PeppermintSnow/ml-in-c/blob/web/static/img/transparent-social-card.png?raw=true)

<div align="center">
  
[![License](https://img.shields.io/badge/MIT_License-6A0DAD.svg?style=for-the-badge&logo=readdotcv&logoColor=white)](./LICENSE)
[![Docs](https://img.shields.io/badge/Docs-6A0DAD.svg?style=for-the-badge&logo=readme&logoColor=white)](https://peppermintsnow.github.io/ml-in-c)
[![C](https://img.shields.io/badge/made_in_c-6A0DAD.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/compiled_with_CMake-6A0DAD.svg?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Solo](https://img.shields.io/badge/Solo_project-6A0DAD.svg?style=for-the-badge&logo=refinedgithub&logoColor=white)](https://github.com/PeppermintSnow)

</div>

**ML-in-C** is a machine learning library written entirely in **pure C**. It aims to provide a complete machine learning toolkit with a primary focus on **performance**, **low-level understanding**, and **experimental development**. 

Please note that **ML-in-C is not intended for production or commercial use!**

Instead, this library is designed for:

- Gaining a deeper understanding of machine learning algorithms
- Practicing systems-level development in C
- Experimenting with memory layout, performance, and control

If you are curious about how machine learning libraries work, ML-in-C offers an environment open to experimentation.

## Installation

**Prerequisites**:  
- [CMake 4.1.1](https://cmake.org/download/)  
- [GCC 15.2.1](https://gcc.gnu.org/install/)

```bash
git clone -b main --single-branch git@github.com:PeppermintSnow/ml-in-c.git && cd ml-in-c
mkdir build && cd build
cmake ..
make
```

Refer to the [Installation guide](https://peppermintsnow.github.io/ml-in-c/docs/getting-started/installation) for a more comprehensive guide.

## Basic Usage
```c
# Create a DataFrame from array
int main() {
    double X[] = {1, 2, 3, 4, 5, 6};
    int lenX = sizeof(X) / sizeof(X[0]);
    char columnName[] = "numbers";
    DataFrame *df = DF_fromArray(X, lenX, columnName);
}

# More examples soon...
```
## Links

<div align="center">

[![Website](https://img.shields.io/badge/Website-6A0DAD.svg?style=for-the-badge&logo=firefoxbrowser&logoColor=white)](https://peppermintsnow.github.io/ml-in-c)
[![API](https://img.shields.io/badge/API_References-6A0DAD.svg?style=for-the-badge&logo=readthedocsdevdotto&logoColor=white)](https://peppermintsnow.github.io/ml-in-c/api/dataframe)
[![Logs](https://img.shields.io/badge/Dev_Logs-6A0DAD.svg?style=for-the-badge&logo=devdotto&logoColor=white)](https://peppermintsnow.github.io/ml-in-c/blog)
[![Research](https://img.shields.io/badge/Research_Notes-6A0DAD.svg?style=for-the-badge&logo=openaccess&logoColor=white)](https://peppermintsnow.github.io/ml-in-c/notes)

</div>



