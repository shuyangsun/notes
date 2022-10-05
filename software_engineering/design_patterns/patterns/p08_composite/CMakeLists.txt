add_executable(p08_composite "patterns/p08_composite/main.cc" "patterns/p08_composite/composite.cc")

target_link_libraries(p08_composite absl::status)