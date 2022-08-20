cmake_minimum_required(VERSION 3.16)
project(stdoutcmt)
set(effective_cpp_VERSION_MAJOR 0)
set(effective_cpp_VERSION_MINOR 1)
set(effective_cpp_VERSION_PATCH 0)

option(TESTS "Build test cases, default value is ON." ON)

set(CMAKE_CXX_STANDARD 17)
set(CPP_STANDARD_COMPILE_FLAGS "-std=c++17")
set(OPTIMIZATION_FLAG_DEBUG "-O0")
set(OPTIMIZATION_FLAG_RELEASE "-Ofast")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_RELEASE}")
add_definitions(${CPP_STANDARD_COMPILE_FLAGS})

include_directories("include")

add_executable(stdoutcmt "src/main.cpp")

if ("${TESTS}" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    include(${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
endif ()
