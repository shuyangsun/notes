[Home](../../README.md) >> [C++](../../README.md#c++) >> [C++ Primer](./README.md)

# C++ Primer

## Templates

### Variadic Tempaltes

Templates cause code bloat since compiler has to generate a version of the template for each type, variadic templates are even more so. Pull common logic out into a function to prevent code bloat.

```c++
// Common logic
std::string JoinStrImpl(std::initializer_list<std::string_view> strs);

template <typename,... S>
std::string Join(const S&... strs) {
  return JoinStrImpl({strs...});
}
```
