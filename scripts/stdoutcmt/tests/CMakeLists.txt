# Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(nlohmann_json 3.11.2 REQUIRED)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/tests")

include_directories("../tests")
add_executable(src_parsing tests/unit/src_parsing.cpp)
target_link_libraries(src_parsing gtest_main nlohmann_json::nlohmann_json)
add_executable(utility tests/unit/utility.cpp)
target_link_libraries(utility gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)

gtest_discover_tests(
    src_parsing
    TEST_PREFIX unit::
)

gtest_discover_tests(
        utility
        TEST_PREFIX unit::
)
