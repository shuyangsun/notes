#include <iostream>
#include <initializer_list>

#include "cpp_notes/util/print.h"

class Widget {
 public:
  Widget() {
    std::cout << "calling default constructor..." << std::endl;
  }

  Widget(int i, bool b) {
    std::cout << "calling (int, bool) constructor..." << std::endl;
  }

  Widget(int i, double d) {
    std::cout << "calling (int, double) constructor..." << std::endl;
  }

  Widget(const Widget& other) {
    std::cout << "calling copy constructor..." << std::endl;
  }

  Widget& operator=(const Widget& rhs) {
    std::cout << "calling copy assignment operator..." << std::endl;
    return *this;
  }
};

class WidgetWithInitList {
 public:
  WidgetWithInitList() {
    std::cout << "calling default constructor..." << std::endl;
  }

  WidgetWithInitList(int i, bool b) {
    std::cout << "calling (int, bool) constructor..." << std::endl;
  }

  WidgetWithInitList(int i, double d) {
    std::cout << "calling (int, double) constructor..." << std::endl;
  }

  WidgetWithInitList(std::initializer_list<double> lst) {
    std::cout << "calling (initializer_list<double>) constructor..." << std::endl;
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

  Widget w3(1, true); //> calling (int, bool) constructor...
  Widget w4{1, true}; //> calling (int, bool) constructor...
  Widget w5(1, 0.5);  //> calling (int, double) constructor...
  Widget w6{1, 0.5};  //> calling (int, double) constructor...

  WidgetWithInitList w7(); // WARNING: Empty parentheses interpreted as a function declaration.
  WidgetWithInitList w8{};           //> calling default constructor...
  WidgetWithInitList w9(1, true);    //> calling (int, bool) constructor...
  WidgetWithInitList w10{1, true};   //> calling (initializer_list<double>) constructor...
  WidgetWithInitList w11(1, 0.5);    //> calling (int, double) constructor...
  WidgetWithInitList w12{1, 0.5};    //> calling (initializer_list<double>) constructor...
  WidgetWithInitList w13{0.5, 3.14}; //> calling (initializer_list<double>) constructor...
  #pragma cmt end

  return 0;
}
