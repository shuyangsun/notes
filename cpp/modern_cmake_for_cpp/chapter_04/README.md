[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 4](./README.md)

# Chapter 4: Setting Up Your First CMake Project

Cross compilation: using a specialized toolchain that allows a compiler running on one platform to produce artifactsfor another platform.

## Basics

Calling `cmake_minimum_required()` also applies policies for the specified version, so that upgrading CMake won't break the build.

## Project structure

Don't use `include()`, use `add_subdirectory()` instead, which creates a new scope.

```cmake
# When EXCLUDE_FROM_ALL is specified, the target won't be configured by default. This is useful for example projects.
add_subdirectory(sourc_dir [binary_dir] [EXCLUDE_FROM_ALL])
```
