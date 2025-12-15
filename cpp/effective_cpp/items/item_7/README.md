[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 7](./README.md)

# Item 7: Distinguish between `()` and `{}` when creating objects.

Design your constructors so that the client is not effected by whether they use `()` or `{}` initializer.

Three main ways to initialize a variable:

1. Equal sign: `int x = 1;`
2. Parentheses: `int x(1);`
3. Braces: `int x{1};`

(You can also use equal sign and braces: `int x = {1};`, usually it's treated the same as the brace syntax.)

## Key Differences

1. Braces check for narrowing conversions.
2. For user-defined types the difference could be significant.

```c++
Widgeet w1;  // calls default constructor: Widget()
Widget w2 = w1;  // calls copy constructor: Widget(const Widget& other)
w1 = w2;  // calls copy assignment: Widget& operator=(const Widget& rhs)
```

3. Braces and equal sign can also initialize non-static data members.

```c++
class Widget {
  //...
 private:
  int x{0};
  int y = 0;
  // int z(0); // *** COMPILE ERROR ***
};
```

4. `Widget w();` is parsed as function declaration instead of object construction. Only `Widget w;` or `Widget w{};` calls the default constructor.
5. Empty braces `{}` calls default constructor, not empty `std::initializer_list` constructor.
6. In constructor calls:
   1. If no constructor declares a parameter of `std::initializer_list`: braces and parenthesis behave the same.
   2. If one or more constructor declares a parameter of `std::initializer_list`: the overloading rule _strongly_ prefers the initializer_list version. (However, narrowing conversion is not allowed inside braces, **only if there's no way to convert the types of the arguments to `initializer_list`, the compiler would fallback to other constructors**.)

```c++
class Widget1 {
 public:
  Widget1(int a, double b) { /* ... */ }
  Widget1(std::initializer_list<bool> il) { /* ... */ }
};

Widget1 w1{2, 5.3}; // ERROR: narrowing conversion
```

```c++
class Widget2 {
 public:
  Widget2(int a, double b) { /* ... */ }
  Widget2(std::initializer_list<std::string> il) { /* ... */ }
};

Widget2 w2{2, 5.3}; // Calls the first constructor
```

_Note that in the following example, the book described a different behavior than what actually happened for `Widget3`._

```c++
class Widget3 {
 public:
  Widget3(const Widget3& other) { /* ... */ }
  Widget3(std::initializer_list<float> il) { /* ... */ }
  operator float() const { /* ... */ }
};

Widget3 w3_1{};
Widget3 w3_2{w3_1};  // Calls copy ctor (but the book says it calls initializer_list ctor)
```
