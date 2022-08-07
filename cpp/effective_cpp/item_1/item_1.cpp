#include <iostream>
#include <boost/type_index.hpp>

#define PRINT_DEDUCED_TYPE() std::cout << \
  "ParamType: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << ", " << \
  "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;

// Case 1:

template<typename T>
void f_ref(T& param) {
  PRINT_DEDUCED_TYPE();
}

template<typename T>
void f_ptr(T* param) {
  PRINT_DEDUCED_TYPE();
}

// Case 2:

template<typename T>
void f_uref(T&& param) {
  PRINT_DEDUCED_TYPE();
}

// Case 3:

template<typename T>
void f_byval(T param) {
  PRINT_DEDUCED_TYPE();
}

int main(int argc, char **argv) {
  int x = 27;
  const int cx = x;
  const int& rx = x;
  const int* px = &x;

  std::cout << "Case 1:" << std::endl;

  f_ref(x);    // ParamType: int&, T: int
  f_ref(cx);   // ParamType: int const&, T: int const
  f_ref(rx);   // ParamType: int const&, T: int const
  f_ref(px);   // ParamType: int const*&, T: int const*

  std::cout << std::endl;

  f_ptr(&x);   // ParamType: int*, T: int
  f_ptr(&cx);  // ParamType: int const*, T: int const
  f_ptr(&rx);  // ParamType: int const*, T: int const
  f_ptr(px);   // ParamType: int const*, T: int const

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl;

  f_uref(x);   // ParamType: int&, T: int&
  f_uref(cx);  // ParamType: int const&, T: int const&
  f_uref(rx);  // ParamType: int const&, T: int const&
  f_uref(px);  // ParamType: int const*&, T: int const*&
  f_uref(27);  // ParamType: int&&, T: int

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl;

  f_byval(x);  // ParamType: int, T: int
  f_byval(cx); // ParamType: int, T: int
  f_byval(rx); // ParamType: int, T: int
  f_byval(px); // ParamType: int const*, T: int const*

  return 0;
}