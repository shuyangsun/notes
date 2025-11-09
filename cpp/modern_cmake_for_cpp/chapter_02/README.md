[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 2](./README.md)

# Chapter 2: The CMake Language

Four building blocks: comments, commands, variables and control structures.

## Comment

Examples: [comments.cmake](./comments.cmake)

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

Examples: [arguments.cmake](./arguments.cmake)

Under the hood, the only data type recognized by CMake is a `STRING`. CMake _evaluates_ every argument to a static string and pass them into the command. Evaluation means string interpolation, which includes escaping, expanding variable reference, or unpacking lists.

Three types of arguments:

- Bracket arguments: raw strings, usually used to pass multi-line strings.
- Quoted arguments: similar to C++ strings, but interpolate variable references and can span multiple lines. Does not split the string with the list delimiter `;`.
- Unquoted arguments: Same as quoted arguments, except that it splits the string with `;` into a list.

```cmake
message(STATUS "hello;WORLD") # Output: -- hello;WORLD
message(STATUS hello;WORLD)   # Output: -- helloWORLD
```

## Variables

Examples: [variables.cmake](./variables.cmake)

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

## Scope

Examples: [scope.cmake](./scope.cmake)

Two kinds of scopes:

- File: used when blocks and custom functions are executed within a file.
- Directory: used when `add_subdirectory()` is called.

> NOTE: condition, loop and macro blocks don't create extra scope.

When a nested scope is created, a copy of all variables from outer scope is created. Changes made to variables in the inner scope does not propagate back to outer scope. Even when a variable is `unset()`, it is only unset in the inner scope.

The only way to propagate change back to outer scope is `block(PROPAGATE VAR)` or `set(VAR "val" PARENT_SCOPE)`. If `PARENT_SCOPE` is used, it doesn't change the variable in the current scope.

New File scope can be created with `block()` or `function()`, but not `macro()`.

```cmake
# Creating new File scope
block()
  # New File scope
endblock()

function()
  # New File scope
endfunction()
```

## Lists

Lists can be created by passing multiple arguments to `set()` or with `;` delimeter.

```cmake
set(LIST_1 this is a list)
set(LIST_2 "this;is;also;a;list")
set(LIST_3 here is "another;list")

message(${LIST_1}) # thisisalist
message(${LIST_2}) # thisisalsoalist
message(${LIST_3}) # hereisanotherlist

list(LENGTH LIST_1 LIST_1_LEN)
message(${LIST_1_LEN}) # 4
```

## Control structure

### Conditional blocks

Examples: [condition.cmake](condition.cmake)

Note that no local variable scope is created by conditional blocks or loops.

Strings evaluated to `True`: `ON`, `Y`, `YES`, `TRUE` or a non-zero number (case-insensitive).

Strings evaluated to `False`: `OFF`, `N`, `NO`, `FALSE`, `IGNORE`, `NOTFOUND`, `.*-NOTFOUND` (string ending in `-NOTFOUND`), empty string, zero.

Conditional evaluations in CMake is very tricky! There are many unintuitive behaviors. Check out examples in [condition.cmake](condition.cmake) and be aware of the following DOs and DON'Ts.

```cmake
# DON'Ts
if(VAR) # Not evaluating value of ${VAR}, checking if VAR is defined.
if(DEFINED ${VAR}) # Not checking if VAR is defined, but checking if variable named as value of ${VAR} is defined.

# DOs
# checking if VAR is defined
if(DEFINED VAR)
if(DEFINED CACHE{VAR})
if(DEFINED ENV{VAR})

if("${VAR}") # checking if value of ${VAR} is ON, Y, YES, TRUE, or non-zero number.
```

Commonly used comparison operators:

- `EQUAL`, `LESS`, `LESS_EQUAL`, `GREATER`, `GREATER_EQUAL`.
- `VERSION_LESS_EQUAL` (and other `VERSION_` comparisons).
- `STREQUAL`.
- `MATCHES`: `if(<VAR> MATCHES <regex>)`.
- `INLIST`: `if(<VAR> INLIST <LIST_VAR>)`.
- `COMMAND`, `POLICY`, `TEST`, `TARGET`.
- Working with file system (should be avoided by preferring higher level approaches first): `EXISTS`, `IS_NEWER_THAN`, `IS_DIRECTORY`, `IS_SYMLINK`, `IS_ABSOLUTE`, `PATH_EQUAL`.

### Loops

The only loop that restricts new variables in the local scope is `foreach`.

Examples: [loop.cmake](loop.cmake)

```cmake
set(COLORS "red;green;blue")
# foreach(COLOR IN LISTS "${COLORS}") # does not work
foreach(COLOR IN LISTS COLORS) # works
    message([=[COLOR is ]=] "${WORD}")
endforeach()
message([=[Value of IDX_2 outside of "foreach" loop is: ]=] "${IDX_2}") # empty
```

## Commands

Use `function()`, avoid using `macro()`.

Functions create a local variable scope, macros don't, so they can affect global state. Variables passed into macros also behave in a strange way, they are not treated as real variables, but a find-and-replace.
