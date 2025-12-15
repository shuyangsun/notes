[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 9](./README.md)

# Item 9: Prefer alias declarations to `typedef`s.

Alias declarations are easier to read and can be used with templates which `typedef`s cannot. Using types defined with `typedef`s inside of a template requires prefixing with `typename` (it is a _dependent type_), this is not the case for alias declarations.

## Type Traits

Type transformation functions introduced to `type_traits` C++11 were implemented with nested `typedefs` instead of alias declarations. In C++14, `_t` versions using alias declarations are added to STL.

```c++
// C++11
tempalte<typename T>
class MyClass {
  typename std::add_lvalue_reference<T>::type t_ref;
};

// C++14
tempalte<typename T>
class MyClass {
  std::add_lvalue_reference_t<T> t_ref;
};
```
