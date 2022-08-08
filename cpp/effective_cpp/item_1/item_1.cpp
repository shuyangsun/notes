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
  const int& rx = x;
  char ch = 'a';
  char const * const pc = &ch;
  const char ac[] = "Effective C++ Notes";

  std::cout << "Case 1:" << std::endl;

  f_ref(x);    // ParamType: int&, T: int
  f_ref(cx);   // ParamType: int const&, T: int const
  f_ref(rx);   // ParamType: int const&, T: int const
  // f_ref(27);   // Does not compile
  f_ref(pc);   // ParamType: char const* const&, T: char const* const
  f_ref(ac);   // ParamType: char const (&) [20], T: char const [20]
  f_ref(MyFunc);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_cref(x);    // ParamType: int const&, T: int
  f_cref(cx);   // ParamType: int const&, T: int
  f_cref(rx);   // ParamType: int const&, T: int
  f_cref(27);   // int const&, T: int
  f_cref(pc);   // ParamType: char const* const&, T: char const*
  f_cref(ac);   // ParamType: char const (&) [20], T: char [20]
  f_cref(MyFunc);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_ptr(&x);   // ParamType: int*, T: int
  f_ptr(&cx);  // ParamType: int const*, T: int const
  f_ptr(&rx);  // ParamType: int const*, T: int const
  // f_ptr(27);   // Does not compile
  // f_ptr(&27);  // Does not compile
  f_ptr(pc);   // ParamType: char const*, T: char const
  f_ptr(ac);   // ParamType: char const*, T: char const
  f_ptr(MyFunc);   // ParamType: void (*)(int, double), T: void (int, double)

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl;

  f_uref(x);   // ParamType: int&, T: int&
  f_uref(cx);  // ParamType: int const&, T: int const&
  f_uref(rx);  // ParamType: int const&, T: int const&
  f_uref(27);  // ParamType: int&&, T: int
  f_uref(pc);  // ParamType: char const* const&, T: char const* const&
  f_uref(ac);  // ParamType: char const (&) [20], T: char const (&) [20]
  f_uref(MyFunc);  // ParamType: void (&)(int, double), T: void (&)(int, double)

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl;

  f_byval(x);  // ParamType: int, T: int
  f_byval(cx); // ParamType: int, T: int
  f_byval(rx); // ParamType: int, T: int
  f_byval(27); // ParamType: int, T: int
  f_byval(pc); // ParamType: char const*, T: char const*
  f_byval(ac); // ParamType: char const*, T: char const*
  f_byval(MyFunc); // ParamType: void (*)(int, double), T: void (*)(int, double)

  std::cout << std::endl;

  f_cbyval(x);  // ParamType: int const, T: int
  f_cbyval(cx); // ParamType: int const, T: int
  f_cbyval(rx); // ParamType: int const, T: int
  f_cbyval(27); // ParamType: int const, T: int
  f_cbyval(pc); // ParamType: char const* const, T: char const*
  f_cbyval(ac); // ParamType: char const* const, T: char const*
  f_cbyval(MyFunc); // ParamType: void (* const)(int, double), T: void (*)(int, double)

  std::cout << std::endl;
  std::cout << "Array size deduction:" << std::endl;
  std::cout << "Size of char array \"" << ac << "\" is " << ArraySize(ac) << std::endl;

  return 0;
}