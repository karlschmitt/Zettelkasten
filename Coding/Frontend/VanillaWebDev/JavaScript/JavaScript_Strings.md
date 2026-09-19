---
id: 20260919153612
title: JavaScript String Tutorial
author: Karl Schmitt
date: 2026-09-19
---

# JavaScript String Tutorial

Here is a comprehensive tutorial on JavaScript strings, covering creation, common properties, methods, and templates.

***

## 1. Creating Strings

You can create strings in JavaScript using three types of quotes.

```javascript
// Single and Double quotes are functionally identical
let greeting = 'Hello, World!';
let message = "JavaScript is fun";

// Backticks create Template Literals (supports embedded variables and multiline text)
let name = "Alex";
let status = `Welcome back, ${name}!`; 
```

## 2. Key String Properties

Strings have built-in properties to help you inspect them:

*
* `.length`: Returns the total number of characters (including spaces and punctuation).
* Indexing: Access individual characters using square brackets `[]` starting at `0`.
*

```javascript
let text = "Code";
console.log(text.length); // Output: 4
console.log(text[0]);     // Output: "C"
```

## 3. Essential String Methods

JavaScript strings are immutable (cannot be changed directly), so these methods always return a _new_ string.

| Method                            | Description                                                                 | Example                                     |
| --------------------------------- | --------------------------------------------------------------------------- | ------------------------------------------- |
| `toLowerCase()` / `toUpperCase()` | Changes text casing                                                         | `"Hi".toUpperCase()` → `"HI"`               |
| `trim()`                          | Removes whitespace from both ends                                           | `" hi ".trim()` → `"hi"`                    |
| `includes(substring)`             | Checks if a search term exists (returns `true`/`false`)                     | `"Coding".includes("Code")` → `true`        |
| `indexOf(substring)`              | Returns the starting index of a term (or `-1` if not found)                 | `"Hello".indexOf("l")` → `2`                |
| `slice(start, end)`               | Extracts a section of a string from `start` up to (but not including) `end` | `"JavaScript".slice(0, 4)` → `"Java"`       |
| `replace(old, new)`               | Replaces the first match of a term with a new one                           | `"Java".replace("Java", "Type")` → `"Type"` |
| `split(separator)`                | Splits a string into an array of substrings                                 | `"a-b-c".split("-")` → `["a", "b", "c"]`    |

***

## 4. Template Literals & Interpolation

Template literals (using backticks \` \`) make string concatenation much cleaner by allowing you to inject variables directly into the text using `${variable}`.

```javascript
let item = "laptop";
let price = 999;

// Old way (Concatenation)
let oldStyle = "The " + item + " costs \$" + price + ".";

// New way (Template Literals)
let newStyle = `The ${item} costs $${price}.`;
```

***

Would you like to try some interactive practice exercises, or should we move on to learning about JavaScript arrays?

