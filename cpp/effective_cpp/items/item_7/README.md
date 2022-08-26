[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 7](./README.md)

# Item 7: Distinguish between `()` and `{}` when creating objects.

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
5. In constructor calls:
   1. If no constructor declares a parameter of `std::initializer_list`: braces and parenthesis behave the same.
   2. If one or more constructor declares a parameter of `std::initializer_list`: the overloading rule *strongly* prefers the initializer_list version, even when narrowing conversion is necessary.