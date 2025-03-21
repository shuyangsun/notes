[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 2](./README.md)

# Chapter 2: The CMake Language

Four building blocks: comments, commands, variables and control structures.

## Comment

```cmake
# This is a one-line comment.

#[==[
This is
a multi-line
comment.
]==]#  <-- closing number of equal signs must match opening
```

## Command

Commands aren't case-sensitive, but `snake_case` commands are preferred.

Command invocations in CMake are not expressions, everything inside of the parenthesis is treated as an argument.

```cmake
message(STATUS "Hello!" message("Hello!"))

# Output:
# -- Hello!message(Hello!)
```

### Command arguments

Under the hood, the only data type recognized by CMake is a `STRING`. CMake _evaluates_ every argument to a static string and pass them into the command. Evaluation means string interpolation, which includes escaping, expanding variable reference, or unpacking lists.

Three types of arguments:

- Bracket arguments: raw strings, usually used to pass multi-line strings.
- Quoted arguments: similar to C++ strings, but interpolate variable references and can span multiple lines. Does not split the string with the list delimiter `;`.
- Unquoted arguments: Same as quoted arguments, except that it splits the string with `;` into a list.

```cmake
message(STATUS "hello;WORLD") # Output: -- hello;WORLD
message(STATUS hello;WORLD)   # Output: -- helloWORLD
```

### Variables

Variables and keywords (`VERSION` in `project(Prj VERSION 1.2.3)`) are case-sensitive.

```cmake
set(MyString1 "Text1")
set([[My String2]] "Text2")
set("My String 3" "Text3")
message(STATUS ${MyString1})     # -- Text1
message(STATUS ${My\ String2})   # -- Text2
message(STATUS ${My\ String\ 3}) # -- Text3

set(MY_VAR_1 "value of MY_VAR_1")
set(MY_VAR_2 MY_VAR_1)
set(${MY_VAR_2} "value of something") # bad idea, don't do this

message("Value of MY_VAR_1: " \ ${MY_VAR_1}) # value of something
message("Value of MY_VAR_2: " \ ${MY_VAR_2}) # MY_VAR_1
```

Three types of variable references:

```cmake
# Normal variable
set(<variable> <value>)
message(${MY_NORMAL_VAR})

# Cache variable
set(<variable> <value> CACHE <type> <docstring> [FORCE])
message($CACHE{MY_CACHE_VAR})

# Environment variable
MY_ENV_VAR=foo cmake -S <source-tree> -B <build-tree>
message($ENV{MY_ENV_VAR})
```

- `${}`: reference normal or cached variables.
- `$CACHE{}`: reference cache variables.
  - Not available in scripts, only project files.
  - Persisted in `CMakeCache.txt`, new value written if did not exists or `FORCE`.
  - Available types: `BOOL`, `PATH`, `FILEPATH`, `STRING`, `INTERNAL`.
- `$ENV{}`:reference environment variables.
  - Changes to environment variables within CMake files won't affect the actual system environment variable.
  - CMake copies environment variables during the generation time and stores them in the build tree, so later changes to environment variables won't take effect without a fresh build.

Cache variables caching behavior:

```cmake
# ======= Step 1 =======

# CMakeLists.txt
set(CACHE_VAR_TEST False CACHE BOOL "Test cache variable")

$ cmake -S <source-tree> -B <build-tree>

# CMakeCache.txt
# //Test cache variable
# CACHE_VAR_TEST:BOOL=False

# ======= Step 2 =======
# CMakeLists.txt
set(CACHE_VAR_TEST True CACHE BOOL "Test cache variable")

$ cmake -S <source-tree> -B <build-tree>

# CMakeCache.txt
# //Test cache variable
# CACHE_VAR_TEST:BOOL=False <-------- still False

# ======= Step 3 =======
# CMakeLists.txt
set(CACHE_VAR_TEST True CACHE BOOL "Test cache variable" FORCE)

$ cmake -S <source-tree> -B <build-tree>

# CMakeCache.txt
# //Test cache variable
# CACHE_VAR_TEST:BOOL=True <-------- changed to True
```

### Scope

TODO
