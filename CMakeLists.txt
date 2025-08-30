cmake_minimum_required(VERSION 4.0)
project(ml_in_c C)
set(CMAKE_C_STANDARD 99)

enable_testing()

# Source
add_library(ml_in_c STATIC
    src/datatypes/dataframe.c
)

# Headers
target_include_directories(ml_in_c PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Add tests
add_executable(test_ml_in_c
    test/datatypes/dataframe.c
)

target_link_libraries(test_ml_in_c ml_in_c)

# Register tests
add_test(NAME test_ml_in_c COMMAND test_ml_in_c)

# `ctest` to run tests
