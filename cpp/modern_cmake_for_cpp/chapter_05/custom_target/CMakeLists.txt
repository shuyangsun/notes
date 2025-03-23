cmake_minimum_required(VERSION 3.26)

project(CustomTargetExample VERSION 2025.03.23.132800 LANGUAGES CXX)

add_custom_target(hello ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/hello.cmake
    COMMENT "Saying hello."
)

add_custom_target(checksum_display ALL
    COMMAND ${CMAKE_COMMAND} -E sha256sum ${CMAKE_CURRENT_BINARY_DIR}/main
    COMMENT "Displaying checksum of main executable."
)

add_custom_target(checksum_save ALL
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/checksum.cmake
    BYPRODUCTS main.ck
    COMMENT "Saving artifacts checksum."
)

add_executable(main main.cc)
add_dependencies(main hello)
add_dependencies(checksum_display main)
add_dependencies(checksum_save main checksum_display)
