#include <iostream>
#include <vector>

#include "cpp_notes/util/print.h"

std::vector<int> v_global;

template<typename T>
void ResetV(const T& new_value) {
  v_global = new_value;
}

template<typename T>
T InitVec() {
  return {1,2, 3};
}

int main(int argc, char **argv) {

  #pragma cmt beg
  cppn::util::PrintPlatform(); //> Mac OS: Clang version 13.1.6 (clang-1316.0.21.2.5)
  #pragma cmt end

  #pragma cmt beg -1
  auto x = 27; //> int
  PRINT_TYPE(x);

  const auto cx = x; //> int const
  PRINT_TYPE(cx);

  auto& rx = x; //> int&
  PRINT_TYPE(rx);

  auto& crx = cx; //> int const&
  PRINT_TYPE(crx);

  auto&& rval = 27; //> int&&
  PRINT_TYPE(rval);

  auto&& rx2 = x; //> int&
  PRINT_TYPE(rx2);

  auto&& rx3 = cx; //> int const&
  PRINT_TYPE(rx3);

  auto&& rx4 = rx; //> int&
  PRINT_TYPE(rx4);

  auto&& rx5 = crx; //> int const&
  PRINT_TYPE(rx5);

  auto x2(27); //> int
  PRINT_TYPE(x2);

  auto x3 = {27}; //> std::initializer_list<int>
  PRINT_TYPE(x3);

  auto x4{27}; //> int
  PRINT_TYPE(x4);

  // std::vector<int> vec1 = InitVec();  // *** COMPILE ERROR ***
  auto vec2 = InitVec<std::vector<int>>(); //> std::__1::vector<int, std::__1::allocator<int> >
  PRINT_TYPE(vec2);
  #pragma cmt end

  std::vector<int> v;
  auto reset_v = [&v](const auto& new_value) { v = new_value; };
  // resetV({1, 2, 3});  // *** COMPILE ERROR ***
  reset_v(std::vector<int>{1, 2, 3});

  // ResetV({1, 2, 3});  // *** COMPILE ERROR ***
  ResetV(std::vector<int>{1, 2, 3});

  return 0;
}