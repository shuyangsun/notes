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

include_directories("../tests")

add_executable(unit_test tests/unit_test.cpp)

target_link_libraries(unit_test gtest_main ${EXTRA_LIBS})

include(GoogleTest)
gtest_discover_tests(unit_test)
