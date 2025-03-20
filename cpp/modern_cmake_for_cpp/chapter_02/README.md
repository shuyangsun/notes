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

Variables and keywords (`VERSION` in `project(Prj VERSION 1.2.3)`) are case-sensitive.

```cmake
set(MyString1 "Text1")
set([[My String2]] "Text2")
set("My String 3" "Text3")
message(STATUS ${MyString1})     # -- Text1
message(STATUS ${My\ String2})   # -- Text2
message(STATUS ${My\ String\ 3}) # -- Text3
```

### Scoping

TODO
