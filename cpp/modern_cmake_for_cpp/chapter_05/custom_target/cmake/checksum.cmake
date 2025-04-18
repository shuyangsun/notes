include_guard(GLOBAL)

file(SHA256 "${CMAKE_CURRENT_BINARY_DIR}/main" MAIN_CHECKSUM)

set(CHECKSUM_DIR "${CMAKE_CURRENT_BINARY_DIR}/checksum")
make_directory("${CHECKSUM_DIR}")
file(WRITE "${CHECKSUM_DIR}/main.ck" "${MAIN_CHECKSUM}")
