[Home](../../../README.md) >> [Frontend](../../../README.md#frontend) >> [CSS: The Definitive Guide](./README.md)

# CSS: The Definitive Guide by [Eric Meyer](https://meyerweb.com/eric/)

## 1. CSS Fundamentals

### Different ways of linking

#### 1. _\<link>_ tag

```html
<!-- index.html -->
<head>
  <!-- title, type, and media are optional -->
  <link
    rel="stylesheet"
    href="my_style.css"
    title="Default"
    type="text/css"
    media="screen, print"
  />
</head>
```

#### 2. _\<style>_ element

```html
<!-- index.html -->
<head>
  <style>
    p {
      color: red;
    }
  </style>
</head>
```

#### 3. _@import_ directive

```css
/* my_style.css */
@import url(my_style_2.css);

/* Media descriptors are optional. */
@import url(my_style_3.css) all;
@import url(my_style_4.css) screen;
@import url(my_style_5.css) screen, print;
```

## 2. Selectors

Demo: [02_selectors.html](./02_selectors.html)

### Type Selectors

_Type selectors_, previously known as _element selectors_, often select HTML elements, but not always (works with XML too).
