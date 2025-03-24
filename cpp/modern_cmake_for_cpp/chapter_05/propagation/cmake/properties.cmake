include_guard(GLOBAL)

# This INTERFACE simply sets the compiler warning flags for targets linked to it.
add_library(properties_compiler_warning INTERFACE)
target_compile_options(properties_compiler_warning INTERFACE
    -Wall -Wextra -Wpedantic
)
