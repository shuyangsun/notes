[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 2](./README.md)

# Item 2: Understand `auto` type deduction.

`auto` type deduction is template type deduction, with `auto` plays the role of `T` and the type specifier as `ParamType`. Refer to [Item 1: Understand template type deduction](../item_1) for detail.

For example, `const auto& x = y;` would be equivalent in below template type deduction:

```c++
template<typename T>
void f(const T& param);

f(y);
```

One caveat is that the only syntax `auto` would deduce to `std::initializer_list` is with `auto val = {27}`. In this case `auto` is deduced to `std::initializer_list<int>`. The other syntax: `auto val{27}` no longer deduce to `std::initializer_list<int>` after [proposal N3922](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3922.html).
