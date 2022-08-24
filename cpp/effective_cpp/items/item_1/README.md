[Home](../../../../README.md) >> [C++](../../../../README.md#c++) >> [Effective Modern C++](../../README.md) >> [Item 1](./README.md)

# Item 1: Understand template type deduction.

```c++
template<typename T>
void f(ParamType param);

f(expr);
```

Deduced type for `T` and `ParamType` varies based on how they are specified and what is `expr`. There are three main scenarios categorized by `ParamType`.

`ParamType` is:
1. Pointer or reference type, but not a universal reference (`T&` or `T*`).
2. Universal reference (`T&&`).
3. Neither a pointer nor a reference (`T`).

## Case 1: `ParamType` is Reference or Pointer

1. If `expr`'s type is a reference, ignore the reference part.
2. Pattern-match `expr`'s type against `ParamType` to determine `T`.

Note that if `ParamType` is declared as `T&`, attempting to pass in an rvalue `expr` will not compile, but it will if `ParamType` is `const T&`.

### Example 1

```c++
template<typename T>
void f(T& param);
```

| expr                 | Deduced `ParamType` | Deduced `T`      |
|----------------------|---------------------|------------------|
| `int x = 27;`        | `int&`              | `int`            |
| `const int cx = x;`  | `const int&`        | `const int`      |
| `const int& rx = x;` | `const int&`        | `const int`      |
| `f(27);`             | Does not compile    | Does not compile |

### Example 2

```c++
template<typename T>
void f(const T& param);
```

| expr                 | Deduced `ParamType` | Deduced `T` |
|----------------------|---------------------|-------------|
| `int x = 27;`        | `const int&`        | `int`       |
| `const int cx = x;`  | `const int&`        | `int`       |
| `const int& rx = x;` | `const int&`        | `int`       |
| `f(27);`             | `const int&`        | `int`       |

## Case 2: `ParamType` is Universal Reference

It is declared similar to the rvalue syntax (but it's not, see [item_24](../item_24) for universal references). It is the only situation where deduction depends on lvalue-ness and rvalue-ness of `expr`.

1. If `expr` is an lvalue, both `T` and `ParamType` are deduced to be lvalue references (only situation `T` is deduced to a reference).
2. If `expr` is a rvalue, [Case 1](#case-1-ref-or-pointer) rules apply.

Note: To force an rvalue in the parameter, use `const T&&` instead. See function `f_curef` in [item_1.cpp](item_1.cpp) for example.

### Example

```c++
template<typename T>
void f(T&& param);
```

| expr                 | Deduced `ParamType` | Deduced `T`  |
|----------------------|---------------------|--------------|
| `int x = 27;`        | `int&`              | `int&`       |
| `const int cx = x;`  | `const int&`        | `const int&` |
| `const int& rx = x;` | `const int&`        | `const int&` |
| `3`                  | `int&&`             | `int`        |

## Case 3: `ParamType` is neither a Pointer nor a Reference

Everything is pass-by-value (copies will be made).

1. If `expr`'s type is a reference, ignore the reference part.
2. Ignore `const` and `volatile` if they are present.

### Example

```c++
template<typename T>
void f(T param);
```

| expr                 | Deduced `ParamType` | Deduced `T` |
|----------------------|---------------------|-------------|
| `int x = 27;`        | `int`               | `int`       |
| `const int cx = x;`  | `int`               | `int`       |
| `const int& rx = x;` | `int`               | `int`       |

## Summary
`ParamType` determines how types get deduced. Simple cases like `T` and `T&` behave as expected intuitively: `T` always makes a copy (thus the lost of `const` and `volatile`) and `T&` just does pattern matching. The tricky scenario is when `ParamType` is `T&&` (universal reference) and `expr` is an lvalue reference. In this case, both `ParamType` and `T` are deduced to lvalue reference type, this is also the only situation where `T` is deduced to be reference type.

Refer to [item_1.cpp](item_1.cpp) for actual program output in different situations.