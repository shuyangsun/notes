#include <unistd.h>

#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;
  while (true) {
    std::cout << "sleeping..." << std::endl;
    sleep(1);
  }
  return 0;
}
