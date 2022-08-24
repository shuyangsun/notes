#include <iostream>
#include <initializer_list>

#include "cpp_notes/util/print.h"

int main(int argc, char **argv) {
  #pragma cmt beg
  int x = 1;
  int y(1);
  int z{1};

  int p = {1};
  auto q{1}; PRINT_TYPE(q);    //> int
  auto r = {1}; PRINT_TYPE(r); //> std::initializer_list<int>

  std::initializer_list<int> u{1, 2};
  std::initializer_list<int> v = {1, 2};
  #pragma cmt end
  return 0;
}
