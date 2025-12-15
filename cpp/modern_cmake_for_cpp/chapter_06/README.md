[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 6](./README.md)

# Chapter 6: Using Generator Expressions

Generator expressions are used to fetch data that are not yet availble during configuration, but are available during generation. They are evaluated when configuration is complete and the build system is created.

```cmake
$<EXPRESSION:arg1,arg2,arg3...>
```

Unless explicitly specified (e.g., via an argument), the context of a generator expression is the target using that expression.

## Dos and Don'ts

```cmake
# Dos

$<IF:condition,true_string> # explicitly use the IF expression
```

```cmake
# Don'ts

$<UPPER_CASE:${variable}> # don't mix with variables
$<condition:true_string> # bad, breaks the convension of using expression name first
```

## Conditional expansion

```cmake
$<IF:condition,true_string,false_string>
$<IF:condition,true_string,>
$<condition:true_string>

$<NOT:arg>
$<AND:arg1,arg2,arg3...>
$<OR:arg1,arg2,arg3...>
$<BOOL:string_arg>

$<STREQUAL:arg1,arg2>
$<EQUAL:arg1,arg2> # converts string to number before comparison
$<IN_LIST:arg,list>
$<VERSION_EQUAL:v1,v2>
$<VERSION_LESS:v1,v2>
$<VERSION_LESS_EQUAL:v1,v2>
$<VERSION_GREATER:v1,v2>
$<VERSION_GREATER_EQUAL:v1,v2>
$<PATH_EQUAL:path1,path2> # without normalization
```

`$<BOOL:string_arg>` evaluates to `true` if none of these conditions are met:

- The string is empty.
- The string matches any of the following (case-insensitive): `0`, `FALSE`, `OFF`, `N`, `NO`, `IGNORE`, or `NOTFOUND`.
- The string ends in `-NOTFOUND` (case-insensitive).

## Queries

```cmake
$<TARGET_EXISTS:arg>

$<LOWER_CASE:string>
$<UPPER_CASE:string>

$<IN_LIST:string,list>
$<JOIN:list,delim> # joins list with "delim"
$<REMOVE_DUPLICATES:list> # without sorting
$<FILTER:list,INCLUDE|EXCLUDE,regex>

# After CMake 3.24:
# For most HAS_... queries, there is also a GET_... version.
$<PATH:HAS_ROOT_NAME,path>
$<PATH:HAS_ROOT_DIRECTORY,path>
$<PATH:HAS_ROOT_PATH,path>
$<PATH:HAS_FILENAME,path>
$<PATH:HAS_EXTENSION,path>
$<PATH:HAS_STEM,path>
$<PATH:HAS_RELATIVE_PART,path>
$<PATH:HAS_PARENT_PATH,path>

$<PATH:IS_ABSOLUTE,path>
$<PATH:IS_RELATIVE,path>
$<PATH:IS_PREFIX[,NORMALIZE],prefix,path>

$<PATH:CMAKE_PATH[,NORMALIZE],path...>
$<PATH:APPEND,path...,input,...>
$<PATH:REMOVE_FILENAME,path...>
$<PATH:REPLACE_FILENAME,path...,input>
$<PATH:REMOVE_EXTENSION[,LAST_ONLY],path...>
$<PATH:REPLACE_EXTENSION[,LAST_ONLY],path...,input>
$<PATH:NORMAL_PATH,path...>
$<PATH:RELATIVE_PATH,path...,base_directory>
$<PATH:ABSOLUTE_PATH[,NORMALIZE],path...,base_directory>

# After CMake 3.27:
https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html
```
