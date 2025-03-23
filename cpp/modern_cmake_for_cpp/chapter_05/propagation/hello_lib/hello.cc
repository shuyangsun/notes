#include "hello.h"

#include <iostream>

namespace hello_lib {

void HelloPrintable::Print() const { std::cout << "Hello!" << std::endl; }

}  // namespace hello_lib
