[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 5](./README.md)

# Item 5: Prefer `auto` to explicit type declarations.

This is very debatable. For example, at the time of this writing (2022-08-22), the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Type_deduction) explicitly specified "Use type deduction only if it makes the code clearer to readers who aren't familiar with the project, or if it makes the code safer. Do not use it merely to avoid the inconvenience of writing an explicit type.".

Given all the quirks `auto` and `decltype(auto)` comes with, one should avoid over-using `auto` at everywhere.

However, there are a few cases where it is almost always beneficial to use `auto` instead of explicitly defined types:

## Lambda Expressions

Lambda expressions defined with `auto` is almost certain to be (much) faster than explicitly typed `std::function` objects. `std::function` objects are quite heavy-duty, but `auto` deduced version performs similarly to normal functions. See [item_5.cpp](item_5.cpp) for performance difference and deduced type for the `auto` version.

```c++
auto lt_1 = [](const int& a, const int& b) -> bool { return a < b; };  // faster

std::function<bool(const int&, const int&)> lt_2 \
  = [](const auto& a, const auto& b) -> bool { return a < b; };  // slower
```

## Iterator Types

Using `auto` for iterators prevents mistakes and makes code more readable and maintainable.

```c++
std::unordered_map<std::string, int> m{};
// Initialize ...

// Should be std::pair<const std::string, int>
for (const std::pari<std::string, int>& p: m) { // Implicit copy
  // ..
}

for (const auto& [k, v]: m) { // Much easier to read

}
```
