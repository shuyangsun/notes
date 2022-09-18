#include <iostream>

enum Color {
  RED,
  GREEN,
  BLUE,
};

// auto RED = false;  // *** COMPILE ERROR *** Redefinition of 'RED' as different kind of symbol

enum class Hardware {
  CPU,
  GPU
};

auto CPU = 1;  // fine

// enum MyEnum1; // *** COMPILE ERROR *** ISO C++ forbids forward references to 'enum' types
enum class MyEnum2; // ok

int main(int argc, char **argv) {
  return 0;
}

enum class MyEnum2 {
  VAL_1,
  VAL_2
};
