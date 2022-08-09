#include <iostream>
#include <boost/type_index.hpp>

#include "cpp_notes/util/print.h"

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

template<typename T>
void f_curef(const T&& param) {
  PRINT_DEDUCED_TYPE();
}

template<typename T>
void f_uref_with_init(T&& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE();
  T t_default{};
  std::cout << "Value of T{}: " << t_default << std::endl;
}

// Case 3:

template<typename T>
void f_byval(T param) {
  PRINT_DEDUCED_TYPE();
}

template<typename T>
void f_cbyval(const T param) {
  PRINT_DEDUCED_TYPE();
}

template<typename T, std::size_t N>
constexpr std::size_t ArraySize(T (&)[N] ) noexcept {
  return N;
}

void MyFunc(int, double) {}

int main(int argc, char **argv) {
  int x = 27;
  const int cx = x;
  int& rx = x;
  const int& rcx = x;
  char ch = 'a';
  char const * const pc = &ch;
  const char ac[] = "Effective C++ Notes";

  std::cout << "Case 1:" << std::endl;

  PLN<__LINE__>(); f_ref(x);    // ParamType: int&, T: int
  PLN<__LINE__>(); f_ref(cx);   // ParamType: int const&, T: int const
  PLN<__LINE__>(); f_ref(rx);   // ParamType: int&, T: int
  PLN<__LINE__>(); f_ref(rcx);   // ParamType: int const&, T: int const
  // PLN<__LINE__>(); f_ref(27);   // *** COMPILE ERROR ***
  PLN<__LINE__>(); f_ref(pc);   // ParamType: char const* const&, T: char const* const
  PLN<__LINE__>(); f_ref(ac);   // ParamType: char const (&) [20], T: char const [20]
  PLN<__LINE__>(); f_ref(MyFunc);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  PLN<__LINE__>(); f_cref(x);    // ParamType: int const&, T: int
  PLN<__LINE__>(); f_cref(cx);   // ParamType: int const&, T: int
  PLN<__LINE__>(); f_cref(rx);   // ParamType: int const&, T: int
  PLN<__LINE__>(); f_cref(rcx);   // ParamType: int const&, T: int
  PLN<__LINE__>(); f_cref(27);   // ParamType: int const&, T: int
  PLN<__LINE__>(); f_cref(pc);   // ParamType: char const* const&, T: char const*
  PLN<__LINE__>(); f_cref(ac);   // ParamType: char const (&) [20], T: char [20]
  PLN<__LINE__>(); f_cref(MyFunc);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  PLN<__LINE__>(); f_ptr(&x);   // ParamType: int*, T: int
  PLN<__LINE__>(); f_ptr(&cx);  // ParamType: int const*, T: int const
  PLN<__LINE__>(); f_ptr(&rx);  // ParamType: int*, T: int
  PLN<__LINE__>(); f_ptr(&rcx);  // ParamType: int const*, T: int const
  // PLN<__LINE__>(); f_ptr(27);   // *** COMPILE ERROR ***
  // PLN<__LINE__>(); f_ptr(&27);  // *** COMPILE ERROR ***
  PLN<__LINE__>(); f_ptr(pc);   // ParamType: char const*, T: char const
  PLN<__LINE__>(); f_ptr(ac);   // ParamType: char const*, T: char const
  PLN<__LINE__>(); f_ptr(MyFunc);   // ParamType: void (*)(int, double), T: void (int, double)

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl;

  PLN<__LINE__>(); f_uref(x);   // ParamType: int&, T: int&
  PLN<__LINE__>(); f_uref(cx);  // ParamType: int const&, T: int const&
  PLN<__LINE__>(); f_uref(rx);  // ParamType: int&, T: int&
  PLN<__LINE__>(); f_uref(rcx);  // ParamType: int const&, T: int const&
  PLN<__LINE__>(); f_uref(27);  // ParamType: int&&, T: int
  PLN<__LINE__>(); f_uref(pc);  // ParamType: char const* const&, T: char const* const&
  PLN<__LINE__>(); f_uref(ac);  // ParamType: char const (&) [20], T: char const (&) [20]
  PLN<__LINE__>(); f_uref(MyFunc);  // ParamType: void (&)(int, double), T: void (&)(int, double)

  std::cout << std::endl;

  // PLN<__LINE__>(); f_curef(x);   // *** COMPILE ERROR ***
  // PLN<__LINE__>(); f_curef(cx);  // *** COMPILE ERROR ***
  // PLN<__LINE__>(); f_curef(rx);  // *** COMPILE ERROR ***
  // PLN<__LINE__>(); f_curef(rcx);  // *** COMPILE ERROR ***
  PLN<__LINE__>(); f_curef(27);  // ParamType: int const&&, T: int
  // PLN<__LINE__>(); f_curef(pc);  // *** COMPILE ERROR ***
  // PLN<__LINE__>(); f_curef(ac);  // *** COMPILE ERROR ***
  PLN<__LINE__>(); f_curef(MyFunc);  // ParamType: void (&&)(int, double), T: void (int, double)

  std::cout << std::endl;

  // f_uref_with_init(x, __LINE__);  // *** COMPILE ERROR ***
  f_uref_with_init(cx, __LINE__);  // ParamType: int const&, T: int const&
  // f_uref_with_init(rx, __LINE__);  // *** COMPILE ERROR ***
  f_uref_with_init(rcx, __LINE__);  // ParamType: int const&, T: int const&

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl;

  PLN<__LINE__>(); f_byval(x);  // ParamType: int, T: int
  PLN<__LINE__>(); f_byval(cx); // ParamType: int, T: int
  PLN<__LINE__>(); f_byval(rx); // ParamType: int, T: int
  PLN<__LINE__>(); f_byval(rcx); // ParamType: int, T: int
  PLN<__LINE__>(); f_byval(27); // ParamType: int, T: int
  PLN<__LINE__>(); f_byval(pc); // ParamType: char const*, T: char const*
  PLN<__LINE__>(); f_byval(ac); // ParamType: char const*, T: char const*
  PLN<__LINE__>(); f_byval(MyFunc); // ParamType: void (*)(int, double), T: void (*)(int, double)
  // PLN<__LINE__>(); f_byval({1, 2, 3}); // *** COMPILE ERROR ***

  std::cout << std::endl;

  PLN<__LINE__>(); f_cbyval(x);  // ParamType: int const, T: int
  PLN<__LINE__>(); f_cbyval(cx); // ParamType: int const, T: int
  PLN<__LINE__>(); f_cbyval(rx); // ParamType: int const, T: int
  PLN<__LINE__>(); f_cbyval(rcx); // ParamType: int const, T: int
  PLN<__LINE__>(); f_cbyval(27); // ParamType: int const, T: int
  PLN<__LINE__>(); f_cbyval(pc); // ParamType: char const* const, T: char const*
  PLN<__LINE__>(); f_cbyval(ac); // ParamType: char const* const, T: char const*
  PLN<__LINE__>(); f_cbyval(MyFunc); // ParamType: void (* const)(int, double), T: void (*)(int, double)

  std::cout << std::endl;
  std::cout << "Array size deduction:" << std::endl;
  std::cout << "Size of char array \"" << ac << "\" is " << ArraySize(ac) << std::endl;

  return 0;
}