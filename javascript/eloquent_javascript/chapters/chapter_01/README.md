[Home](../../../README.md) >> [JavaScript](../../../README.md#javascript) >> [Eloquent JavaScript](../../README.md) >> [Values, Types, and Operators](./README.md)

# Chapter 1: Values, Types, and Operators

## Numbers

- All JavaScript numbers are signed 64-bits.

```js
2.998e8; // ~ speed of light (m/s) in scientific notation

// Special numbers

1 / 0; // Infinity
0 / 0; // NaN
-1 / 0; // -Infinity

Infinity + 1; // Infinity
Infinity - 1; // Infinity
Infinity * 2; // Infinity

-Infinity - 1; // -Infinity
-Infinity + 1; // -Infinity
-Infinity * 2; // -Infinity

Number.MAX_VALUE * 2; // Infinity
-Number.MAX_VALUE * 2; // -Infinity

Number.MAX_VALUE + 1; // 1.7976931348623157e+308
Number.MIN_VALUE / 2; // 0
Number.MIN_VALUE - 1; // -1
-Number.MAX_VALUE; // -1.7976931348623157e+308
-Number.MAX_VALUE - 1; // -1.7976931348623157e+308

Infinity === Infinity; // true
Infinity === -Infinity; // true
NaN === NaN; // false
NaN !== NaN; // true
```
