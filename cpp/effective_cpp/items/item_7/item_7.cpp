#include <iostream>
#include <string>
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

class WidgetIL1 {
 public:
  WidgetIL1() {
    std::cout << "calling default constructor..." << std::endl;
  }

  WidgetIL1(int i, bool b) {
    std::cout << "calling (int, bool) constructor..." << std::endl;
  }

  WidgetIL1(int i, double d) {
    std::cout << "calling (int, double) constructor..." << std::endl;
  }

  WidgetIL1(std::initializer_list<double> il) {
    std::cout << "calling (initializer_list<double>) constructor..." << std::endl;
  }
};

class WidgetIL2 {
 public:
  WidgetIL2(int i, double d) {
    std::cout << "calling (int, double) constructor..." << std::endl;
  }

  WidgetIL2(std::initializer_list<bool> il) {
    std::cout << "calling (initializer_list<bool>) constructor..." << std::endl;
  }
};

class WidgetIL3 {
 public:
  WidgetIL3(int i, double d) {
    std::cout << "calling (int, double) constructor..." << std::endl;
  }

  WidgetIL3(std::initializer_list<std::string> il) {
    std::cout << "calling (initializer_list<std::string>) constructor..." << std::endl;
  }
};

class WidgetIL4 {
 public:
  WidgetIL4() {
    std::cout << "calling default constructor..." << std::endl;
  }

  WidgetIL4(const WidgetIL4& other) {
    std::cout << "calling copy constructor..." << std::endl;
  }

  WidgetIL4(std::initializer_list<float> il) {
    std::cout << "calling (initializer_list<float>) constructor..." << std::endl;
  }

  operator float() const {
    return 1.0f;
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

  WidgetIL1 w7();           // WARNING: Empty parentheses interpreted as a function declaration.
  WidgetIL1 w8{};           //> calling default constructor...
  WidgetIL1 w9({});         //> calling (initializer_list<double>) constructor...
  WidgetIL1 w10{{}};        //> calling (initializer_list<double>) constructor...
  WidgetIL1 w11(1, true);   //> calling (int, bool) constructor...
  WidgetIL1 w12{1, true};   //> calling (initializer_list<double>) constructor...
  WidgetIL1 w13(1, 0.5);    //> calling (int, double) constructor...
  WidgetIL1 w14{1, 0.5};    //> calling (initializer_list<double>) constructor...
  WidgetIL1 w15{0.5, 3.14}; //> calling (initializer_list<double>) constructor...

  // WidgetIL2 w16{3, 5.5}; // *** COMPILE ERROR *** Type 'double' cannot be narrowed to 'bool' in initializer list
  WidgetIL3 w17{3, 5.5}; //> calling (int, double) constructor...

  WidgetIL4 w18{};    //> calling default constructor...
  WidgetIL4 w19(w18); //> calling copy constructor...
  WidgetIL4 w20{w18}; //> calling copy constructor...
  #pragma cmt end

  return 0;
}
