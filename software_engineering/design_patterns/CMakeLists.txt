cmake_minimum_required(VERSION 3.16)
project(design_patterns)
set(design_patterns_VERSION_MAJOR 0)
set(design_patterns_VERSION_MINOR 1)
set(design_patterns_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CPP_STANDARD_COMPILE_FLAGS "-std=c++17")
set(OPTIMIZATION_FLAG_DEBUG "-O0")
set(OPTIMIZATION_FLAG_RELEASE "-Ofast")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_RELEASE}")
add_definitions(${CPP_STANDARD_COMPILE_FLAGS})

find_package(absl REQUIRED)
set(ABSL_BUILD_TESTING, ON)
set(ABSL_USE_GOOGLETEST_HEAD, ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

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

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/patterns)

FOREACH(subdir ${SUBDIRS})
    STRING(REGEX MATCH "^p[0-9]+_[a-z_]+$" pattern_loc "${subdir}")
    SET(cmake_loc "${CMAKE_CURRENT_SOURCE_DIR}/patterns/${subdir}/CMakeLists.txt")
    IF(NOT "${pattern_loc}" STREQUAL "" AND EXISTS ${cmake_loc})
        INCLUDE(${cmake_loc})
    ENDIF()
ENDFOREACH()
