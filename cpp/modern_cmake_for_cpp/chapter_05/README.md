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

Extends the functionality of the build system beyound what's provided out of the box. Custom targets do not apply the staleness check, they are not part of the dependency tree.

Can be used to:

- Calculate checksums.
- Run code sanitizer.
- Send compilation reports to some pipeline.

```cmake
add_custom_target(Name [ALL] [COMMAND commands...])
```

Use `cmake --graphviz=deps.dot -S <src-tree> -b <build-tree>` to generate graphviz of dependencies.

## Setting properties of targets

Many commands uses properties under the hood, see [here](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html) for the full list.

```cmake
get_target_property(<var> <target> <property-name>)
set_target_properties(<target1> <target2> ...
    PROPERTIES
    <property-1> <value-1>
    <property-2> <value-2>
    ...
)
```

## Transitive usage requirements

When target A depends on target B, we can say the _destination target_ A _uses_ the _source target_ B.

Property propagation keywords:

- `PRIVATE`: only sets the property on the source target (no propagation).
- `INTERFACE`: sets the property on only the destination target.
- `PUBLIC`: sets the property on both source and destination target.

Propagation keywords when calling `target_link_library()` controls how far the propagation travels in the dependency tree.

Important properties managed with the `set_target_properties()` command: `COMPILE_DEFINITIONS`, `COMPILE_FEATURES`, `COMPILE_OPTIONS`, `INCLUDE_DIRECTORIES`, `LINK_DEPENDS`, `LINK_DIRECTORIES`, `LINK_LIBRARIES`, `LINK_OPTIONS`, `POSITION_INDEPENDENT_CODE`, `PRECOMPILE_HEADERS`, `SOURCES`.

## Dealing with conflicting propagated properties

See [propagation/printable_api/CMakeLists.txt](./propagation/printable_api/CMakeLists.txt) and [propagation/hello_lib/CMakeLists.txt](./propagation/hello_lib/CMakeLists.txt) as examples on how to ensure interface compatibility.
