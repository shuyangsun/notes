[Home](../../../README.md) >> [C++](../../../README.md#c++) >> [Modern CMake for C++](../README.md) >> [Chapter 5](./README.md)

# Chapter 5: Working with Targets

A CMake target represents a logical unit that focuses on a specific objective, it can be created with one of these three commands: `add_executable()`, `add_library()`, and `add_custom_target()`.

When a target is built, it generates an artifact that can be utilized by other targets or as the output of the final build process.

"Artifact" can be many things: header files, objects, generated source files, configurations, etc.

In GNU Make, a taget can be a `.cpp` file compiled into a `.o` object file or a group of object files packaged into a `.a` static library.

## Defining executable targets

```cmake
add_executable(<NAME>
    [WIN32] [MACOSX_BUNDLE]
    [EXCLUDE_FROM_ALL]
    <source-files>
)
```

The `WIN32` keyboard prevents the program from showing the default console. The `MACOSX_BUNDLE` makes the target launchable from the Finder as GUI app.

## Defining library targets

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
    [EXCLUDE_FROM_ALL]
    <source-files>
)
```

## Custom targets

Extends the functionality of the build system beyound what's provided out of the box. Custom targets do not apply the staleness check.

Can be used to:

- Calculate checksums.
- Run code sanitizer.
- Send compilation reports to some pipeline.

```cmake
add_custom_target(Name [ALL] [COMMAND commands...])
```
