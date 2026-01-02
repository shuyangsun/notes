[Home](../../../README.md) >> [JavaScript](../../../README.md#javascript) >> [Eloquent JavaScript](../../README.md) >> [Program Structure](./README.md)

# Chapter 2: Program Structure

Some statements require a semicolon at the end , some don't. It's best practice to always add a semicolon at the end of a statement.

<!-- prettier-ignore -->
```javascript
// This is fine.
console.log("Hello, world!")

// Generates error:
// VM92:1 Uncaught TypeError: Cannot read properties of undefined (reading 'forEach')
//    at <anonymous>:1:24
let x = 1
[0, 1, 2].forEach((n) => console.log(n))
```

Imagine bindings (variables) as tentacles rather than boxes - they do not contain values, they grasp them. Empty bindings without initial values are `undefined`.

```javascript
// Multiple binding definition in the same statement:
let one = 1,
  two = 2;
```

`let` was introduced in 2015, it is not the same as `var`. `var` behaves oddly in some situations.

List of reserved keywords: <https://www.w3schools.com/js/js_reserved.asp>
