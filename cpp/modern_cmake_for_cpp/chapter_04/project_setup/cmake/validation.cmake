function(CheckNotInSourceBuild)
    if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
        message(FATAL_ERROR "In-source build is not allowed. You may need to manually delete CMakeCache.txt and CMakeFiles/ directory.")
    endif()
endfunction()

function(CheckPlatformSupport)
    if(NOT (
            CMAKE_SYSTEM_NAME STREQUAL "Linux"
             OR CMAKE_SYSTEM_NAME STREQUAL "Darwin"
             OR CMAKE_SYSTEM_NAME STREQUAL "Windows"
        ))
        message(FATAL_ERROR "Platform ${CMAKE_SYSTEM_NAME} is not supported.")
    endif()
endfunction()

function(CheckCompilerSupport)
    # Supports C++23.
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    # Supports variadic templates.
    list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_23 IsVaridicTemplateSupported)
    if(NOT "${IsVaridicTemplateSupported}")
        message(FATAL_ERROR "C++ 23 is not supported by compiler ${CMAKE_CXX_COMPILER_ID} at ${CMAKE_CXX_COMPILER}.")
    endif()
endfunction()

CheckNotInSourceBuild()
CheckPlatformSupport()
CheckCompilerSupport()
