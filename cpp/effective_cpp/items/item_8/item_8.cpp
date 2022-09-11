#include <iostream>

void f1(int x) { }
void f2(bool x) { }
void f3(void * x) { }

int main(int argc, char **argv) {
  f1(0);
  f1(NULL);
  // f1(nullptr); // *** COMPILE ERROR ***

  f2(0);
  f2(NULL);
  // f2(nullptr); // *** COMPILE ERROR ***

  f3(0);
  f3(NULL);
  f3(nullptr);
  return 0;
}
