cmake_minimum_required(VERSION 3.26)

project(CMakePropagation
    VERSION 2025.03.23.164400
    LANGUAGES CXX
    DESCRIPTION "Demostrates how property propagation can be used to ensure interface compatibility."
)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(printable_api)
add_subdirectory(hello_lib)

add_executable(say_hello main.cc)
target_link_libraries(say_hello PUBLIC printable_api hello_lib)
