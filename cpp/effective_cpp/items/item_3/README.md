# Item 3: Understand `decltype`.

`decltype` is most commonly used in declaring template function return types.

`auto` uses template deduction rules, which is not always desired. `decltype(auto)` comes to rescue, specifying "deduce the type, but use `decltype` rules".

```c++
tempalte<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) {
  authenticateUser();
  return c[i];
}

std::vector<int> v{1, 2, 3};
authAndAccess(v, 1) = 5;  // Does not compile, since 'auto' strips off reference-ness
```

```c++
tempalte<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i) {
  authenticateUser();
  return std::forward(c)[i];
}

std::vector<int> v{1, 2, 3};
authAndAccess(v, 1) = 5;  // Works as intended
```

## Edge Case

Be careful with return statements and function with `decltype(auto)`. See function `f1()` and `f2()` from [item_3.cpp](item_3.cpp) for examples.

```c++
int x{1};
decltype(x); // int
decltype((x)); // int&
```