# Item 7: Distinguish between `()` and `{}` when creating objects.

Three main ways to initialize a variable:

1. Equal sign: `int x = 1;`
2. Parentheses: `int x(1);`
3. Braces: `int x{1};`

(You can also use equal sign and braces: `int x = {1};`, usually it's treated the same as the brace syntax.)

The differences are mainly for user-defined types:

```c++
Widgeet w1;  // calls default constructor: Widget()
Widget w2 = w1;  // calls copy constructor: Widget(const Widget& other)
w1 = w2;  // calls copy assignment: Widget& operator=(const Widget& rhs)
```
