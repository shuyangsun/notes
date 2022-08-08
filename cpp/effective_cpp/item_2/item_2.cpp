#include <iostream>
#include <boost/type_index.hpp>

#define PRINT_TYPE(x) std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>() << std::endl

int main(int argc, char **argv) {
  auto x = 27;  // int
  PRINT_TYPE(x);

  const auto cx = x;  // int const
  PRINT_TYPE(cx);

  auto& rx = x;  // int&
  PRINT_TYPE(rx);

  auto& crx = cx;  // int const&
  PRINT_TYPE(crx);

  auto&& rval = 27;  // int&&
  PRINT_TYPE(rval);

  auto&& rx2 = x;  // int&
  PRINT_TYPE(rx2);

  auto&& rx3 = cx;  // int const&
  PRINT_TYPE(rx3);

  auto&& rx4 = rx;  // int&
  PRINT_TYPE(rx4);

  auto&& rx5 = crx;  // int const&
  PRINT_TYPE(rx5);

  auto x2(27); // int
  PRINT_TYPE(x2);

  auto x3 = {27}; // std::initializer_list<int>
  PRINT_TYPE(x3);

  auto x4{27}; // int
  PRINT_TYPE(x4);

  return 0;
}