#include <memory>

#include "hello.h"
#include "printable_api.h"

int main() {
  std::unique_ptr<printable_api::IPrintable> hello =
      std::make_unique<hello_lib::HelloPrintable>();
  hello->Print();
  return 0;
}
