#include <iostream>
#include <vector>

#include <boost/type_index.hpp>

#include "cpp_notes/util/print.h"

#define PRINT_TYPE(x) std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>() << std::endl

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
  PLN<__LINE__>(); auto x = 27;  // int
  PRINT_TYPE(x);

  PLN<__LINE__>(); const auto cx = x;  // int const
  PRINT_TYPE(cx);

  PLN<__LINE__>(); auto& rx = x;  // int&
  PRINT_TYPE(rx);

  PLN<__LINE__>(); auto& crx = cx;  // int const&
  PRINT_TYPE(crx);

  PLN<__LINE__>(); auto&& rval = 27;  // int&&
  PRINT_TYPE(rval);

  PLN<__LINE__>(); auto&& rx2 = x;  // int&
  PRINT_TYPE(rx2);

  PLN<__LINE__>(); auto&& rx3 = cx;  // int const&
  PRINT_TYPE(rx3);

  PLN<__LINE__>(); auto&& rx4 = rx;  // int&
  PRINT_TYPE(rx4);

  PLN<__LINE__>(); auto&& rx5 = crx;  // int const&
  PRINT_TYPE(rx5);

  PLN<__LINE__>(); auto x2(27); // int
  PRINT_TYPE(x2);

  PLN<__LINE__>(); auto x3 = {27}; // std::initializer_list<int>
  PRINT_TYPE(x3);

  PLN<__LINE__>(); auto x4{27}; // int
  PRINT_TYPE(x4);

  // std::vector<int> vec1 = InitVec();  // *** COMPILE ERROR ***
  PLN<__LINE__>(); auto vec2 = InitVec<std::vector<int>>();
  PRINT_TYPE(vec2);

  std::vector<int> v;
  auto reset_v = [&v](const auto& new_value) { v = new_value; };
  // resetV({1, 2, 3});  // *** COMPILE ERROR ***
  reset_v(std::vector<int>{1, 2, 3});

  // ResetV({1, 2, 3});  // *** COMPILE ERROR ***
  ResetV(std::vector<int>{1, 2, 3});

  return 0;
}