#include <iostream>
#include <boost/type_index.hpp>

#include "cpp_notes/util/print.h"

template<typename T>
void f(T&& param) {
  std::cout << "param: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << ", ";
  std::cout << "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main(int argc, char **argv) {
  #pragma cmt beg

  cppn::util::PrintPlatform(); //> Mac OS: Clang version 14.0.0 (clang-1400.0.29.102)

  int x{1};
  std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name() << std::endl; //> int

  f(x); //> param: int&, T: int&
  #pragma cmt end
  return 0;
}