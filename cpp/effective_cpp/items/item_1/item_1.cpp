#include <iostream>
#include <boost/type_index.hpp>

#define PRINT_DEDUCED_TYPE(line) std::cout << (line) << \
  ": ParamType: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << ", " << \
  "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;

// Case 1:

template<typename T>
void f_ref(T& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

template<typename T>
void f_cref(const T& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

template<typename T>
void f_ptr(T* param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

// Case 2:

template<typename T>
void f_uref(T&& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

template<typename T>
void f_curef(const T&& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

template<typename T>
void f_uref_with_init(T&& param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
  T t_default{};
  std::cout << "Value of T{}: " << t_default << std::endl;
}

// Case 3:

template<typename T>
void f_byval(T param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
}

template<typename T>
void f_cbyval(const T param, const std::size_t line) {
  PRINT_DEDUCED_TYPE(line);
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

  f_ref(x, __LINE__);    // ParamType: int&, T: int
  f_ref(cx, __LINE__);   // ParamType: int const&, T: int const
  f_ref(rx, __LINE__);   // ParamType: int&, T: int
  f_ref(rcx, __LINE__);   // ParamType: int const&, T: int const
  // f_ref(27, __LINE__);   // Does not compile
  f_ref(pc, __LINE__);   // ParamType: char const* const&, T: char const* const
  f_ref(ac, __LINE__);   // ParamType: char const (&) [20], T: char const [20]
  f_ref(MyFunc, __LINE__);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_cref(x, __LINE__);    // ParamType: int const&, T: int
  f_cref(cx, __LINE__);   // ParamType: int const&, T: int
  f_cref(rx, __LINE__);   // ParamType: int const&, T: int
  f_cref(rcx, __LINE__);   // ParamType: int const&, T: int
  f_cref(27, __LINE__);   // int const&, T: int
  f_cref(pc, __LINE__);   // ParamType: char const* const&, T: char const*
  f_cref(ac, __LINE__);   // ParamType: char const (&) [20], T: char [20]
  f_cref(MyFunc, __LINE__);   // ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_ptr(&x, __LINE__);   // ParamType: int*, T: int
  f_ptr(&cx, __LINE__);  // ParamType: int const*, T: int const
  f_ptr(&rx, __LINE__);  // ParamType: int*, T: int
  f_ptr(&rcx, __LINE__);  // ParamType: int const*, T: int const
  // f_ptr(27, __LINE__);   // Does not compile
  // f_ptr(&27, __LINE__);  // Does not compile
  f_ptr(pc, __LINE__);   // ParamType: char const*, T: char const
  f_ptr(ac, __LINE__);   // ParamType: char const*, T: char const
  f_ptr(MyFunc, __LINE__);   // ParamType: void (*)(int, double), T: void (int, double)

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl;

  f_uref(x, __LINE__);   // ParamType: int&, T: int&
  f_uref(cx, __LINE__);  // ParamType: int const&, T: int const&
  f_uref(rx, __LINE__);  // ParamType: int&, T: int&
  f_uref(rcx, __LINE__);  // ParamType: int const&, T: int const&
  f_uref(27, __LINE__);  // ParamType: int&&, T: int
  f_uref(pc, __LINE__);  // ParamType: char const* const&, T: char const* const&
  f_uref(ac, __LINE__);  // ParamType: char const (&) [20], T: char const (&) [20]
  f_uref(MyFunc, __LINE__);  // ParamType: void (&)(int, double), T: void (&)(int, double)

  std::cout << std::endl;

  // f_curef(x, __LINE__);   // Does not compile
  // f_curef(cx, __LINE__);  // Does not compile
  // f_curef(rx, __LINE__);  // Does not compile
  // f_curef(rcx, __LINE__);  // Does not compile
  f_curef(27, __LINE__);  // ParamType: int const&&, T: int
  // f_curef(pc, __LINE__);  // Does not compile
  // f_curef(ac, __LINE__);  // Does not compile
  f_curef(MyFunc, __LINE__);  // ParamType: void (&&)(int, double), T: void (int, double)

  std::cout << std::endl;

  // f_uref_with_init(x, __LINE__);  // Does not compile
  f_uref_with_init(cx, __LINE__);  // ParamType: int const&, T: int const&
  // f_uref_with_init(rx, __LINE__);  // Does not compile
  f_uref_with_init(rcx, __LINE__);  // ParamType: int const&, T: int const&

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl;

  f_byval(x, __LINE__);  // ParamType: int, T: int
  f_byval(cx, __LINE__); // ParamType: int, T: int
  f_byval(rx, __LINE__); // ParamType: int, T: int
  f_byval(rcx, __LINE__); // ParamType: int, T: int
  f_byval(27, __LINE__); // ParamType: int, T: int
  f_byval(pc, __LINE__); // ParamType: char const*, T: char const*
  f_byval(ac, __LINE__); // ParamType: char const*, T: char const*
  f_byval(MyFunc, __LINE__); // ParamType: void (*)(int, double), T: void (*)(int, double)
  // f_byval({1, 2, 3}, __LINE__); // Does not compile

  std::cout << std::endl;

  f_cbyval(x, __LINE__);  // ParamType: int const, T: int
  f_cbyval(cx, __LINE__); // ParamType: int const, T: int
  f_cbyval(rx, __LINE__); // ParamType: int const, T: int
  f_cbyval(rcx, __LINE__); // ParamType: int const, T: int
  f_cbyval(27, __LINE__); // ParamType: int const, T: int
  f_cbyval(pc, __LINE__); // ParamType: char const* const, T: char const*
  f_cbyval(ac, __LINE__); // ParamType: char const* const, T: char const*
  f_cbyval(MyFunc, __LINE__); // ParamType: void (* const)(int, double), T: void (*)(int, double)

  std::cout << std::endl;
  std::cout << "Array size deduction:" << std::endl;
  std::cout << "Size of char array \"" << ac << "\" is " << ArraySize(ac) << std::endl;

  return 0;
}