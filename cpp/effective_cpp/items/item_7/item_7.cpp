#include <iostream>
#include <initializer_list>

#include "cpp_notes/util/print.h"

class Widget {
 public:
  Widget() {
    std::cout << "calling default constructor..." << std::endl;
  }

  Widget(const Widget& other) {
    std::cout << "calling copy constructor..." << std::endl;
  }

  Widget& operator=(const Widget& rhs) {
    std::cout << "calling copy assignment operator..." << std::endl;
    return *this;
  }
};

int main(int argc, char **argv) {
  #pragma cmt beg
  int x = 1;
  int y(1);
  int z{1};

  int p = {1};
  auto q{1}; PRINT_TYPE(q);    //> int
  auto r = {1}; PRINT_TYPE(r); //> std::initializer_list<int>

  std::initializer_list<int> u{1, 2};
  std::initializer_list<int> v = {1, 2};

  Widget w1;      //> calling default constructor...
  Widget w2 = w1; //> calling copy constructor...
  w1 = w2;        //> calling copy assignment operator...

  #pragma cmt end
  return 0;
}
