cmake_minimum_required(VERSION 3.26)

project(CMakeProjectBasics
    VERSION 2025.03.22.203701
    DESCRIPTION [=[Minimum setup for any CMake project.]=]
    HOMEPAGE_URL [=[https://www.shuyangsun.com]=]
    LANGUAGES CXX
)

message([=[]=])

message([=[PROJECT_NAME: ]=] "${PROJECT_NAME}")
message([=[PROJECT_IS_TOP_LEVEL: ]=] "${PROJECT_IS_TOP_LEVEL}")
message([=[CMAKE_PROJECT_NAME: ]=] "${CMAKE_PROJECT_NAME}") # only defined in the top-level CMakeLists.txt
message([=[PROJECT_SOURCE_DIR: ]=] "${PROJECT_SOURCE_DIR}")
message([=[PROJECT_BINARY_DIR: ]=] "${PROJECT_BINARY_DIR}")

message([=[]=])

message([=[PROJECT_VERSION: ]=] "${PROJECT_VERSION}")
message([=[CMakeProjectBasics_PROJECT_VERSION: ]=] "${CMakeProjectBasics_PROJECT_VERSION}")
message([=[CMAKE_PROJECT_VERSION: ]=] "${CMAKE_PROJECT_VERSION}") # only defined in the top-level CMakeLists.txt
message([=[PROJECT_VERSION_MAJOR: ]=] "${PROJECT_VERSION_MAJOR}")
message([=[PROJECT_VERSION_MINOR: ]=] "${PROJECT_VERSION_MINOR}")
message([=[PROJECT_VERSION_PATCH: ]=] "${PROJECT_VERSION_PATCH}")
message([=[PROJECT_VERSION_TWEAK: ]=] "${PROJECT_VERSION_TWEAK}")

message([=[]=])

message([=[PROJECT_DESCRIPTION: ]=] "${PROJECT_DESCRIPTION}")
message([=[CMakeProjectBasics_DESCRIPTION: ]=] "${CMakeProjectBasics_DESCRIPTION}")
message([=[PROJECT_HOMEPAGE_URL: ]=] "${PROJECT_HOMEPAGE_URL}")
message([=[CMakeProjectBasics_HOMEPAGE_URL: ]=] "${CMakeProjectBasics_HOMEPAGE_URL}")

message([=[]=])
