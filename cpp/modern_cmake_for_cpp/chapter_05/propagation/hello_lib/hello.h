#ifndef NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_HELLO_LIB_HELLO_H_
#define NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_HELLO_LIB_HELLO_H_

#include "printable_api.h"

namespace hello_lib {

class HelloPrintable : public printable_api::IPrintable {
 public:
  HelloPrintable() = default;
  ~HelloPrintable() override = default;

  void Print() const final;
};

}  // namespace hello_lib

#endif  // NOTES_CPP_MODERN_CMAKE_FOR_CPP_CHAPTER_05_PROPAGATION_HELLO_LIB_HELLO_H_
