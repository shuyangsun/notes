#include <string>
#include <list>
#include <type_traits>

// Alias declaration version is easier to read:
// Both FP1 and FP2 are pointers to functions that takes an int
// and string argument then returns nothing.
using FP1 = void (*)(int, const std::string&);
typedef void (*FP2)(int, const std::string&);

// Custom allocator
template<typename T>
class MyAlloc {};

// Templatized alias declaration
template<typename T>
using MyAllocList1 = std::list<T, MyAlloc<T>>;

// Nested typedef
template<typename T>
struct MyAllocList2 {
  typedef std::list<T, MyAlloc<T>> type;
};

// Using these aliases:

template<typename T>
class Widget1 {
 private:
  MyAllocList1<T> list;
};

template<typename T>
class Widget2 {
 private:
  typename  MyAllocList2<T>::type list;
};

// Type traits
template<typename T>
class MyClass1 {
 private:
  std::add_lvalue_reference_t<T> val_ref;
};

template<typename T>
class MyClass2 {
 private:
  typename std::add_lvalue_reference<T>::type val_ref;
};

int main(int argc, char **argv) {
  return 0;
}
