#include <iostream>
#include <vector>
#include <utility>

#include <boost/type_index.hpp>

#define PRINT_TYPE(x) std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>() << std::endl

template<typename Container, typename Index>
auto AccessEle_1(Container& c, Index i) -> decltype(c[i]) {
  return c[i];
}

template<typename Container, typename Index>
auto AccessEle_2(Container& c, Index i) {
  return c[i];
}

template<typename Container, typename Index>
decltype(auto) AccessEle_3(Container& c, Index i) {
  return c[i];
}

template<typename Container, typename Index>
decltype(auto) AccessEle_4(Container&& c, Index i) { // Final version (C++14)
  return std::forward<Container>(c)[i];
}

template<typename Container, typename Index>
auto AccessEle_5(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]) { // Final version (C++11)
  return std::forward<Container>(c)[i];
}

int main(int argc, char **argv) {

  #pragma cmt beg
  std::vector<int> v{1, 2, 3};

  AccessEle_1(v, 1) = 5;
  std::cout << v[1];

  // AccessEle_2(v, 1) = 10;  // *** COMPILE ERROR ***

  AccessEle_3(v, 1) = 7;
  std::cout << v[1];

  AccessEle_4(v, 1) = 9;
  std::cout << v[1];

  AccessEle_5(v, 1) = 11;
  std::cout << v[1];
  #pragma cmt end

  return 0;
}