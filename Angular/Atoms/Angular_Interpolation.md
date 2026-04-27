---
id: 20260427115421
title: Angular Interpolation
author: Karl Schmitt
date: 2026-04-27
keywords: []
---

# Angular Interpolation

In Angular, **Interpolation** is a form of one-way data binding that allows you to incorporate dynamic string values into your HTML templates. It is the most common way to display data from the TypeScript component class onto the screen.

Here is a breakdown of how it works technically and practically.

---

### 1. The Syntax
Interpolation uses **double curly braces** `{{ }}` as delimiters. Angular interprets the content between these braces as a **template expression**.

```html
<!-- HTML Template -->
<h1>Hello, {{ title }}</h1>
```

### 2. How it works (Under the hood)
When Angular compiles your application, it follows these steps for interpolation:

1.  **Expression Evaluation:** Angular evaluates the expression inside the `{{ }}` within the context of the component instance.
2.  **String Conversion:** Angular converts the result of that expression into a **string**. If the value is `null` or `undefined`, Angular renders an empty string (it doesn't crash the app).
3.  **DOM Update:** It takes that string and inserts it into the DOM as a text node or as part of an attribute.
4.  **Change Detection:** Whenever Angular’s **Change Detection** cycle runs (e.g., after a click, a timer, or an HTTP response), it re-evaluates the expression. If the value has changed since the last check, Angular updates the DOM automatically.

---

### 3. What can you put inside the braces?
You can use more than just variable names. Angular allows many JavaScript-like expressions:

*   **Property Names:** `{{ userName }}`
*   **Method Calls:** `{{ calculateTotal() }}` (Note: The method must return a value).
*   **Arithmetic:** `{{ 10 + 20 + price }}`
*   **String Concatenation:** `{{ "Welcome " + firstName }}`
*   **Ternary Operators:** `{{ age >= 18 ? 'Adult' : 'Minor' }}`
*   **Pipes:** `{{ birthday | date:'shortDate' }}` (Used to format data before displaying).

---

### 4. What you CANNOT do (Restrictions)
To keep templates clean and secure, Angular restricts certain JavaScript features inside interpolation:

*   **Assignments:** You cannot use `=`, `+=`, or `--`. (e.g., `{{ x = 5 }}` is invalid).
*   **New Keyword:** You cannot use `new` (e.g., `{{ new Date() }}` is invalid; do this in TS instead).
*   **Chaining:** You cannot use `;` to chain multiple statements.
*   **Global Namespace:** You cannot access global variables like `window`, `document`, or `console` directly. You must map them to variables in your TS file first.
*   **Bitwise Operators:** Operators like `|` and `&` are not supported (because `|` is reserved for Angular Pipes).

---

### 5. Security (XSS Protection)
Angular treats interpolation as **data**, not HTML. This means it provides built-in protection against **Cross-Site Scripting (XSS)**.

If your variable contains a script tag:
*   *TS:* `snippet = '<script>alert("Hacked")</script>';`
*   *HTML:* `<div>{{ snippet }}</div>`

Angular will render the actual text `<script>...</script>` on the page rather than executing the script. If you actually *want* to render HTML, you must use **Property Binding** with `[innerHTML]`.

---

### 6. Best Practices
1.  **Keep Expressions Simple:** Don't put complex logic in your HTML. If an expression is longer than a few words, move it into a `getter` or a method in your TypeScript file.
2.  **Avoid Side Effects:** Never use a method in interpolation that changes the state of the application (e.g., a method that updates a counter). Because interpolation runs every time change detection is triggered, side effects can lead to infinite loops or "ExpressionChangedAfterItHasBeenCheckedError".
3.  **Prefer Properties over Methods:** Calling a method `{{ getValues() }}` is more expensive than accessing a property `{{ values }}`, because the method is re-executed every single time Angular checks for changes.