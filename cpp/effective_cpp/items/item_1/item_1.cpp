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
void f_uref_with_init(T&& param) {
  T t_default{};
  std::cout << "T{} is " << t_default << ", ";
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
  int& rx = x;
  const int& rcx = x;
  char ch = 'a';
  char const * const pc = &ch;
  const char ac[] = "Effective C++ Notes";

  #pragma cmt beg

  cppn::util::PrintPlatform(); //> Mac OS: Clang version 14.0.0 (clang-1400.0.29.102)

  std::cout << "Case 1:" << std::endl; //> Case 1:

  f_ref(x);   //> ParamType: int&, T: int
  f_ref(cx);  //> ParamType: int const&, T: int const
  f_ref(rx);  //> ParamType: int&, T: int
  f_ref(rcx); //> ParamType: int const&, T: int const
  // f_ref(27);   // *** COMPILE ERROR ***
  f_ref(pc);     //> ParamType: char const* const&, T: char const* const
  f_ref(ac);     //> ParamType: char const (&) [20], T: char const [20]
  f_ref(MyFunc); //> ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_cref(x);      //> ParamType: int const&, T: int
  f_cref(cx);     //> ParamType: int const&, T: int
  f_cref(rx);     //> ParamType: int const&, T: int
  f_cref(rcx);    //> ParamType: int const&, T: int
  f_cref(27);     //> ParamType: int const&, T: int
  f_cref(pc);     //> ParamType: char const* const&, T: char const*
  f_cref(ac);     //> ParamType: char const (&) [20], T: char [20]
  f_cref(MyFunc); //> ParamType: void (&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_ptr(&x);   //> ParamType: int*, T: int
  f_ptr(&cx);  //> ParamType: int const*, T: int const
  f_ptr(&rx);  //> ParamType: int*, T: int
  f_ptr(&rcx); //> ParamType: int const*, T: int const
  // f_ptr(27);   // *** COMPILE ERROR ***
  // f_ptr(&27);  // *** COMPILE ERROR ***
  f_ptr(pc);     //> ParamType: char const*, T: char const
  f_ptr(ac);     //> ParamType: char const*, T: char const
  f_ptr(MyFunc); //> ParamType: void (*)(int, double), T: void (int, double)

  std::cout << std::endl;
  std::cout << "Case 2:" << std::endl; //> Case 2:

  f_uref(x);      //> ParamType: int&, T: int&
  f_uref(cx);     //> ParamType: int const&, T: int const&
  f_uref(rx);     //> ParamType: int&, T: int&
  f_uref(rcx);    //> ParamType: int const&, T: int const&
  f_uref(27);     //> ParamType: int&&, T: int
  f_uref(pc);     //> ParamType: char const* const&, T: char const* const&
  f_uref(ac);     //> ParamType: char const (&) [20], T: char const (&) [20]
  f_uref(MyFunc); //> ParamType: void (&)(int, double), T: void (&)(int, double)

  std::cout << std::endl;

  // f_curef(x);   // *** COMPILE ERROR ***
  // f_curef(cx);  // *** COMPILE ERROR ***
  // f_curef(rx);  // *** COMPILE ERROR ***
  // f_curef(rcx);  // *** COMPILE ERROR ***
  f_curef(27); //> ParamType: int const&&, T: int
  // f_curef(pc);  // *** COMPILE ERROR ***
  // f_curef(ac);  // *** COMPILE ERROR ***
  f_curef(MyFunc); //> ParamType: void (&&)(int, double), T: void (int, double)

  std::cout << std::endl;

  f_uref_with_init(27);  //> T{} is 0, ParamType: int&&, T: int
  f_uref_with_init(cx);  //> T{} is 0, ParamType: int const&, T: int const&
  f_uref_with_init(rcx); //> T{} is 0, ParamType: int const&, T: int const&
  // f_uref_with_init(x);  // *** COMPILE ERROR ***
  // f_uref_with_init(rx); // *** COMPILE ERROR ***

  std::cout << std::endl;
  std::cout << "Case 3:" << std::endl; //> Case 3:

  f_byval(x);      //> ParamType: int, T: int
  f_byval(cx);     //> ParamType: int, T: int
  f_byval(rx);     //> ParamType: int, T: int
  f_byval(rcx);    //> ParamType: int, T: int
  f_byval(27);     //> ParamType: int, T: int
  f_byval(pc);     //> ParamType: char const*, T: char const*
  f_byval(ac);     //> ParamType: char const*, T: char const*
  f_byval(MyFunc); //> ParamType: void (*)(int, double), T: void (*)(int, double)
  // f_byval({1, 2, 3}); // *** COMPILE ERROR ***

  std::cout << std::endl;

  f_cbyval(x);      //> ParamType: int const, T: int
  f_cbyval(cx);     //> ParamType: int const, T: int
  f_cbyval(rx);     //> ParamType: int const, T: int
  f_cbyval(rcx);    //> ParamType: int const, T: int
  f_cbyval(27);     //> ParamType: int const, T: int
  f_cbyval(pc);     //> ParamType: char const* const, T: char const*
  f_cbyval(ac);     //> ParamType: char const* const, T: char const*
  f_cbyval(MyFunc); //> ParamType: void (* const)(int, double), T: void (*)(int, double)
  #pragma cmt end

  std::cout << std::endl;
  std::cout << "Array size deduction:" << std::endl;
  std::cout << "Size of char array \"" << ac << "\" is " << ArraySize(ac) << std::endl;

  return 0;
}
