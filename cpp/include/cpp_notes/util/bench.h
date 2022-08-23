#ifndef CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_BENCH_H_
#define CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_BENCH_H_

#include <iostream>
#include <chrono>

#define BENCH_DEF(name, k, x) std::size_t _CppNotesBenchFunc_##name () {\
  const auto start{std::chrono::high_resolution_clock::now()};\
  for (std::size_t i{0}; i < (k); ++i) { x; }\
  const auto stop{std::chrono::high_resolution_clock::now()};\
  return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / (k);\
}

#define BENCH(name) _CppNotesBenchFunc_##name()

#endif  // CPP_NOTES_INCLUDE_CPP_NOTES_UTIL_BENCH_H_
