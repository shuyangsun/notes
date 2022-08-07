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
void f_cref(const T& param) {
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
  int const * const px = &x;

  std::cout << "Case 1:" << std::endl;

  f_ref(x);    // ParamType: int&, T: int
  f_ref(cx);   // ParamType: int const&, T: int const
  f_ref(rx);   // ParamType: int const&, T: int const
  f_ref(px);   // ParamType: int const* const&, T: int const* const
  // f_ref(27);   // Does not compile

  std::cout << std::endl;

  f_cref(x);    // ParamType: int const&, T: int
  f_cref(cx);   // ParamType: int const&, T: int
  f_cref(rx);   // ParamType: int const&, T: int
  f_cref(px);   // ParamType: int const* const&, T: int const*
  f_cref(27);   // int const&, T: int

  std::cout << std::endl;

  f_ptr(&x);   // ParamType: int*, T: int
  f_ptr(&cx);  // ParamType: int const*, T: int const
  f_ptr(&rx);  // ParamType: int const*, T: int const
  f_ptr(px);   // ParamType: int const*, T: int const
  // f_ptr(27);   // Does not compile

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl;

  f_uref(x);   // ParamType: int&, T: int&
  f_uref(cx);  // ParamType: int const&, T: int const&
  f_uref(rx);  // ParamType: int const&, T: int const&
  f_uref(px);  // ParamType: int const* const&, T: int const* const&
  f_uref(27);  // ParamType: int&&, T: int

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl;

  f_byval(x);  // ParamType: int, T: int
  f_byval(cx); // ParamType: int, T: int
  f_byval(rx); // ParamType: int, T: int
  f_byval(px); // ParamType: int const*, T: int const*
  f_byval(27); // ParamType: int, T: int

  return 0;
}