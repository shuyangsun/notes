add_executable(p16_iterator "patterns/p16_iterator/p16_iterator.cc" "patterns/p16_iterator/iterator.cc")

target_link_libraries(p16_iterator absl::status)
