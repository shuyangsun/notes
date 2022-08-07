# Item 1: Understand template type deduction.

```c++
template<typename T>
void f(ParamType param);

f(expr);
```

Deducted type for `T` and `ParamType` varies based on how they are specified and what is `expr`. There are three main scenarios categorized by `ParamType`.

`ParamType` is:
1. Pointer or reference type, but not a universal reference (`T&` or `T*`).
2. Universal reference (`T&&`).
3. Neither a pointer nor a reference (`T`).

## Case 1: Ref or Pointer

1. If `expr`'s type is a reference, ignore the reference part.
2. Pattern-match `expr`'s type against `ParamType` to determine `T`.

### Example 1

```c++
template<typename T>
void f(T& param);
```

| expr                 | Deducted `ParamType` | Deducted `T` |
|----------------------|----------------------|--------------|
| `int x = 27;`        | `int&`               | `int`        |
| `const int cx = x;`  | `const int&`         | `const int`  |
| `const int& rx = x;` | `const int&`         | `const int`  |

### Example 2

```c++
template<typename T>
void f(const T& param);
```

| expr                 | Deducted `ParamType` | Deducted `T` |
|----------------------|----------------------|--------------|
| `int x = 27;`        | `const int&`         | `int`        |
| `const int cx = x;`  | `const int&`         | `int`        |
| `const int& rx = x;` | `const int&`         | `int`        |

