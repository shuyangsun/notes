cmake_minimum_required(VERSION 3.26)

project(CMakeCustomCommandDemo
    VERSION 2025.03.24.193800
    LANGUAGES CXX
    DESCRIPTION "Demostrates how to use custom commands."
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(absl REQUIRED)
find_package(Protobuf REQUIRED)

get_filename_component(contact_proto "${CMAKE_CURRENT_SOURCE_DIR}/protos/contact.proto" ABSOLUTE)

get_filename_component(contact_proto_dir "${contact_proto}" DIRECTORY)
get_filename_component(proto_generated_dir "${CMAKE_CURRENT_BINARY_DIR}/protos" ABSOLUTE)

message(STATUS [=[contact.proto path: ]=] "\"${contact_proto}\"")
message(STATUS [=[Generated dir path: ]=] "\"${proto_generated_dir}\"")

make_directory("${proto_generated_dir}")

add_custom_command(
    OUTPUT
    "${proto_generated_dir}/contact.pb.cc"
    "${proto_generated_dir}/contact.pb.h"
    COMMAND protoc ARGS --cpp_out "${proto_generated_dir}" -I "${contact_proto_dir}" "${contact_proto}"
    DEPENDS "${contact_proto}"
    COMMENT "Generating C++ code from \"${contact_proto}\"."
)

add_executable(main main.cc "${proto_generated_dir}/contact.pb.cc")
target_include_directories(main PRIVATE
    "${Protobuf_INCLUDE_DIRS}"
    "${proto_generated_dir}"
)
target_link_libraries(main PRIVATE
    absl::log_internal_check_op
    "${Protobuf_LIBRARIES}"
)
