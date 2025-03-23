add_library(hello_lib STATIC hello.cc)
target_link_libraries(hello_lib PUBLIC printable_api)
target_include_directories(hello_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# If INTERFACE_PRINTABLE_API_VERSION does not match 1.0.1, CMake will produce an
# error during configuration stage.
set_property(TARGET hello_lib PROPERTY INTERFACE_PRINTABLE_API_VERSION 1.0.1)
