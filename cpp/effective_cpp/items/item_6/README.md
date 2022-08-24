# Item 6: Use the explicitly typed initializer idiom when `auto` deduces undesired types.

As a general rule, avoid using `auto` with expressions that generate an instance of an "invisible" proxy class (such as `std::vector<bool>::reference`).

The book recommended using explicit type initializer, but it is arguably much more difficult to read.

```c++
std::vector<bool> vec{true, false, true};

auto ele_1{static_cast<bool>(vec[1])}; // explicit type initializer
bool ele_2{vec[1]}; // Much easier to read
```

Use `static_cast` when you want to explicitly call out the type conversion.
