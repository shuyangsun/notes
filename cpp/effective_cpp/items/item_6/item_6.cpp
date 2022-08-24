#include <iostream>
#include <vector>

#include "cpp_notes/util/print.h"
#include "cpp_notes/util/bench.h"

int main(int argc, char **argv) {
  #pragma cmt beg
  std::vector<bool> vec{true, false, true};

  const auto ele_1{vec[1]}; PRINT_TYPE(ele_1); //> std::__1::__bit_reference<std::__1::vector<bool, std::__1::allocator<bool> >, true> const
  const bool ele_2{vec[1]}; PRINT_TYPE(ele_2); //> bool const

  #pragma cmt end
  return 0;
}