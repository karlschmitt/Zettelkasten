---
id: 20260501132231
title: SASS Variables
author: Karl Schmitt
date: 2026-05-01
---

# SASS Variables

In Angular, **SASS variables** are a way to store information (like colors, fonts, spacing, or sizes) in a name that you can reuse throughout your stylesheets.

Think of them like variables in TypeScript or JavaScript: you define the value once, and if you need to change it later, you only change it in one place.

---

### 1. Syntax

SASS variables always start with a **`$`** symbol.

```scss
// Defining variables
$primary-color: #3f51b5;
$font-stack: 'Roboto', sans-serif;
$standard-padding: 16px;

// Using variables
.button {
  background-color: $primary-color;
  padding: $standard-padding;
  font-family: $font-stack;
}
```
[Try it out ...](./Atoms/Angular_with_SASS.md)

### 2. Why use them in Angular?

*   **Consistency:** If your brand color changes from blue to indigo, you change one variable instead of searching through 50 component files to find every hex code.
*   **Readability:** `$error-red` is much easier to understand than `#d32f2f`.
*   **Calculations:** You can perform math on variables.
    ```scss
    $base-padding: 10px;
    
    .container {
      padding: $base-padding * 2; // Results in 20px
    }
    ```

---

### 3. How to use variables across an Angular App
In Angular, styles are usually **encapsulated** (scoped) to specific components. To use variables globally, you follow these steps:

#### Step A: Create a "Definitions" file
Create a file (usually in `src/styles/`) called `_variables.scss`. (The underscore tells SASS not to compile this into its own CSS file).

```scss
// src/styles/_variables.scss
$primary: #1976d2;
$secondary: #424242;
```

#### Step B: Use them in a Component
In your component’s `.scss` file, you must import that file to access the variables. Modern SASS uses the `@use` rule:

```scss
// src/app/header/header.component.scss
@use 'src/styles/variables' as v;

.header-bar {
  background-color: v.$primary;
}
```

---

### 4. SASS Variables vs. CSS Variables
It is important to know the difference because Angular supports both:

| Feature | SASS Variables (`$var`) | CSS Variables (`--var`) |
| :--- | :--- | :--- |
| **When they work** | **Compile-time:** Converted to hard values when you build the app. | **Runtime:** The browser handles them live. |
| **Dynamic?** | No. You cannot change a SASS variable with JavaScript. | Yes. You can change a CSS variable using `document.documentElement.style.setProperty`. |
| **Scope** | Only available in the SASS files where they are imported. | Global to the DOM tree (inherited). |

**Angular Pro Tip:** Most developers use **SASS variables** for "design tokens" (static things like brand colors and font sizes) and **CSS variables** for things that might change while the user is using the app (like a Light/Dark mode toggle).

### Summary
In Angular, SASS variables help you keep your UI clean and maintainable by storing reusable values behind easy-to-remember names starting with `$`.