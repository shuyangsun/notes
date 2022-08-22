# Item 5: Prefer `auto` to explicit type declarations.

This is very debatable. For example, at the time of this writing (2022-08-22), the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Type_deduction) explicitly specified "Use type deduction only if it makes the code clearer to readers who aren't familiar with the project, or if it makes the code safer. Do not use it merely to avoid the inconvenience of writing an explicit type.".

Given all the quirks `auto` and `decltype(auto)` comes with, maybe it is best to avoid using `auto` in the first place.
