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

### Example 1

```c++
template<typename T>
void f(T& param);
```

| expr                 | Deduced `ParamType` | Deduced `T` |
|----------------------|---------------------|-------------|
| `int x = 27;`        | `int&`              | `int`       |
| `const int cx = x;`  | `const int&`        | `const int` |
| `const int& rx = x;` | `const int&`        | `const int` |

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

## Case 2: Universal Reference

Only situation where deduction depends on lvalue-ness and rvalue-ness of `expr`.

1. If `expr` is an lvalue, both `T` and `ParamType` are deduced to be lvalue references (only situation `T` is deduced to a reference).
2. If `expr` is a rvalue, [Case 1](#case-1-ref-or-pointer) rules apply.

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

## Case 3: Neither a Pointer nor a Reference

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
