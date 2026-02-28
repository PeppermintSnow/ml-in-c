cmake_minimum_required(VERSION 4.0)
project(ml_in_c C)
set(CMAKE_C_STANDARD 99)

enable_testing()

add_library(ml_in_c STATIC)

target_include_directories(ml_in_c PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ml_in_c PRIVATE m)

add_subdirectory(src)
add_subdirectory(test)

install(TARGETS ml_in_c DESTINATION lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include/ml-in-c
    FILES_MATCHING PATTERN "*.h"
)

# Uninstall script
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake")
