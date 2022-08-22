#include <iostream>

#include <boost/type_index.hpp>

template<typename T>
void f(T&& param) {
  std::cout << "param: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << ", ";
  std::cout << "T: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main(int argc, char **argv) {
  #pragma cmt beg
  #pragma cmt end
  return 0;
}