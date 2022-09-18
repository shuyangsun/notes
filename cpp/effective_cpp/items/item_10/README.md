[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 10](./README.md)

# Item 10: Prefer scoped `enum`s to unscoped `enum`s.

Use `enum class` instead of `enum`, they are scoped and more strongly typed (`enum` can be implicitly converted to integral types).

Scoped `enum`s also allow forward declaration.

```c++
enum Color { RED, GREEN, BLUE }; // leaks into scope
auto RED = 1; // *** COMPILE ERROR ***
enum class Hardware { CPU, GPU }; // scoped
auto CPU = 1; // ok
```
