add_executable(p08_composite "patterns/p08_composite/p08_composite_main.cc" "patterns/p08_composite/component.cc")

target_link_libraries(p08_composite absl::status)