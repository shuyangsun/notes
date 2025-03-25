[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 1](./README.md)

# Chapter 1: First Steps with CMake

CMake is the orchestrator that relies on other tools. There are three main stages to build the software.

- Configuration
- Generation
- Build

Generation usually happens right after configuration, so sometimes these two terms are used interchangably.

Developers can provide a `CMakePresets.json` to simplify how users interact with the project.

Avoid calling `make` directly, use `cmake --build` instead.

Files that contain the CMake language are called listfiles, can be included by calling `include()`, `find_package()` and `add_subdirectory()`.

Minimum project file:

```cmake
cmake_minimum_required(VERSION 3.26) # Required
project(MyProject) # Required
```

Package configuration files (Config-files) are named `<PackageName>-config.cmake` or `<PackageName>Config.cmake`, use the `find_package()` command to include packages.

## Commands

### Configuration and generation

```bash
cmake -S <source-tree> -B <build-tree> # Configuration and generation.

cmake -S <source-tree> -B <build-tree> -G <generator> # Specify generator.
cmake --help # Show available generators

# Customize cache variables
# Types: BOOL, FILEPATH, PATH, STRING, INTERNAL
cmake -D <var>:<type>=<value> -S <source-tree> -B <build-tree>

# Example: specify build type for single-configuration generators.
cmake -S <s-tree> -B <b-tree> -D CMAKE_BUILD_TYPE:STRING=Release -G "Ninja"
```

### Build

```bash
cmake --build <build-tree> [-j<jobs>] # Build
cmake --build <build-tree> -t clean # remove artifacts from build tree AFTERWARDS
cmake --build <build-tree> --clean-first # remove artifacts from build tree BEFORE build
```

### Install

```bash
cmake --install <build-tree> --install-prefix <prefix> --config Release
```

### Script

```bash
# Does not run any configuration or generation
cmake [-D <var>=<value>...] -P <script-file> [-- <unparsed options>...]
```

### Single command

Run a command in a platform independent way, only a select list of commands are available.

```bash
cmake -E <command> [options]

# Example
cmake -E sha256sum <path-to-file>
```

Available commands: `capabilities`, `cat`, `chdir`, `compare_files`, `copy`, `copy_directory`, `copy_directory_if_different`, `copy_if_different`, `echo`, `echo_append`, `env`, `environment`, `make_directory`, `md5sum`, `sha1sum`, `sha224sum`, `sha256sum`, `sha384sum`, `sha512sum`, `remove`, `remove_directory`, `rename`, `rm`, `sleep`, `tar`, `time`, `touch`, `touch_nocreate`, `create_symlink`, `create_hardlink`, `true`, and `false`.

### Workflow preset

```bash
cmake --workflow --preset <name>
```
