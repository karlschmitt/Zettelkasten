---
id: 20260919154653
title: JavaScript Template Literals
author: Karl Schmitt
date: 2026-09-19
---

# JavaScript Template Literals

Here is a quick and practical tutorial on JavaScript template literals, which offer a cleaner, modern way to work with strings.

***

## 1. Basic Syntax

Template literals use backticks (`` ` ``) instead of standard single (`'`) or double (`"`) quotes.

```javascript
let basicString = `This is a template literal.`;
```

## 2. String Interpolation (Inserting Variables)

Instead of messy string concatenation with the plus sign (`+`), you can inject variables or expressions directly into the text using the `${expression}` syntax.

* Variables:
  ```javascript
  let user = "Sarah";
  console.log(`Hello, ${user}!`); // Output: Hello, Sarah!
  ```
* Expressions and Math:
  ```javascript
  let price = 20;
  let tax = 0.1;
  console.log(`Total: $${price * (1 + tax)}`); // Output: Total: \$22
  ```

## 3. Multi-line Strings

With normal strings, creating a new line requires adding a newline character (`\n`). Template literals preserve whitespace and newlines exactly as you type them in your code editor.

```javascript
// Old way
let oldWay = "Line one\n" + "Line two";

// Modern way
let htmlTemplate = `
  <div>
    <h1>Heading</h1>
    <p>Paragraph text.</p>
  </div>
`;
```

## 4. Nesting Templates

You can easily nest template literals inside other template literals, which is especially useful when writing conditional logic using ternary operators.

```javascript
let isLoggedIn = true;
let user = "Alex";

let message = `System: ${isLoggedIn ? `Welcome back, \${user}` : "Please log in"}`;
```

***

Would you like to test your knowledge with a few practice exercises, or would you prefer to explore tagged templates next?


