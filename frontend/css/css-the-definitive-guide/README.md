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

### Grouping

Select elements with all classes by chaining class selectors together without any delimeter.

```css
/* Select elements with class="note warning ..." */
.note.warning {
  color: red;
}
```

IDs carry more weight than classes when trying to determine which style should be applied.

### Attribute Selectors

It's possible to chain attributes: `h2[attr1][attr2]`.

Different types of attribute selectors:

| Type                           | Syntax           | Example                | Description                                                                                                    |
| ------------------------------ | ---------------- | ---------------------- | -------------------------------------------------------------------------------------------------------------- |
| Simple                         | `[attr]`         | `h1[class]`            | All `h1` elements with `class` attribute.                                                                      |
| Exact                          | `[attr="val"]`   | `p[lang="en fr"]`      | All `p` elements with `lang` attribute being exactly `"en fr"` (in this order).                                |
| Partial (space separated)      | `[attr~="val"]`  | `img[title~="Figure"]` | All image elements with `title` attribute having value `Figure` in a space-separated list.                     |
| Partial (substring)            | `[attr*="val"]`  | `span[class*="tran"]`  | All `span` elements with `class` attribute's value having substring `tran` (`transparent`, `transition`, etc.) |
| Partial (begins)               | `[attr^="val"]`  | `a[href^="https://"]`  | All `a` elements with `href` attribute's value beginning with `https://`.                                      |
| Partial (ends)                 | `[attr$="val"]`  | `img[src$=".jpg"]`     | All JPEG image elements.                                                                                       |
| Partial (starts with then bar) | `[attr\|="val"]` | `p[lang\|="en"]`       | All `p` elements with `lang` attribute's value starting with `en-` (e.g., `en-us`) or equals to `en`.          |

Including an `i` before the closing bracket of attribute selector changes value matching to be case-insensitive. For example: `img[src$=".jpg" i]` or `p[lang|="en" i]`.

### Using Document Structure

#### Descendent Combinator

The descendent selector is composed of two or more selectors separated by spaces. These spaces are examples of _combinator_. A space combinator can be translated as "found within", "is a descendent of" (not only "is child of").

```css
/* Selects all <li> under <ul>, even when deeply nested. */
ul li {
  color: red;
}
```

The descendent selector has no notion for element proximity, i.e., closeness does not matter. This can cause issues when two selectors have equal specificity weights, in which case the last written rule wins out.

```html
<style>
  div:not(.help) span {
    color: gray;
  }

  div.help span {
    color: red;
  }
</style>

<div class="help">
  <div class="container">
    <!-- Paragraph below will be red, because red is the last written rule, -->
    <!-- even though <p> is closer to div.container. -->
    <p>This is a child of div.container, a descendent of div.help.</p>
  </div>
</div>
```

#### Child Combinator

The child combinator `>` only selects elements that is a direct child (instead of any level of descendent).

```css
h1 > em {
  color: red;
}
```

You can combine descendent and child combinators. There is no operator precedence, the rule reads left to right.

#### Sibling Combinators

The adjacent-sibling combinator `+` only selects sibling that _immediately follows_ the first selector, it does not select all siblings.

The following-sibling combinator `~` only selects sibling that _follows_ the first selector, it does not select siblings before.

Pure text content inbetween elements does not interfere with sibling relationship.

```html
<style>
  /* All styles here will be applied. */
  ul li + li {
    font-style: italic;
  }
  ul li.first + li {
    color: purple;
  }
  ul li.second ~ li {
    border: gray 1px solid;
  }
</style>

<ul>
  <li class="first">Item one.</li>
  <li class="second">Item two.</li>
  Random text.
  <li>Item three.</li>
  <li>Item four.</li>
</ul>
```

## 3. Pseudo-Class and Pseudo-Element Selectors
