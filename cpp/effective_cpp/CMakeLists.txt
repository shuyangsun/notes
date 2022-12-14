cmake_minimum_required(VERSION 3.16)
project(effective_cpp)
set(effective_cpp_VERSION_MAJOR 0)
set(effective_cpp_VERSION_MINOR 1)
set(effective_cpp_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CPP_STANDARD_COMPILE_FLAGS "-std=c++17")
set(OPTIMIZATION_FLAG_DEBUG "-O0")
set(OPTIMIZATION_FLAG_RELEASE "-Ofast")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_RELEASE}")
add_definitions(${CPP_STANDARD_COMPILE_FLAGS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include/")

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost 1.79.0 REQUIRED)

# Macro copied from: https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/items)

FOREACH(subdir ${SUBDIRS})
    STRING(REGEX MATCH "^item_[0-9]+$" item_loc "${subdir}")
    SET(cmake_loc "${CMAKE_CURRENT_SOURCE_DIR}/items/${subdir}/CMakeLists.txt")
    IF(NOT "${item_loc}" STREQUAL "" AND EXISTS ${cmake_loc})
        INCLUDE(${cmake_loc})
    ENDIF()
ENDFOREACH()
