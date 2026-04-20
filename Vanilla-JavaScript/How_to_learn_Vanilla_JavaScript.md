---
id: 20260420165939
title: How to learn Vanilla JavaScript?
name: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript ]
---

# How to learn Vanilla JavaScript?

Learning Vanilla JavaScript (JS) means learning the language itself without using libraries like jQuery or frameworks like React. Since you already know HTML and CSS, you are in the perfect position to start, because **JavaScript’s main job in the browser is to manipulate HTML and CSS.**

Here is a structured roadmap to learning Vanilla JS from scratch.

---

### 1. The Setup (Connecting JS to HTML)
You don't need a special environment. You just need your browser and a text editor (like VS Code). Create an `index.html` file and a `script.js` file.

**The correct way to link them:**
Place the script tag at the bottom of your `<body>` tag so the HTML loads before the script runs.

```html
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1 id="title">Hello World</h1>
    <button id="btn">Click Me</button>

    <script src="script.js"></script>
</body>
</html>
```

---

### 2. The Fundamentals (The "Logic")
Before you change things on the screen, you need to understand how the language thinks.

*   **Variables:** Use `const` (for values that don't change) and `let` (for values that do). Avoid `var`.
*   **Data Types:** Strings ("Hello"), Numbers (10), Booleans (true/false), Arrays ([1,2,3]), and Objects.
*   **Functions:** These are blocks of code that perform a task.
    ```javascript
    const greet = (name) => {
        console.log("Hello " + name);
    };
    greet("User");
    ```

---

### 3. DOM Manipulation (The "Bridge")
The **DOM (Document Object Model)** is how JavaScript "sees" your HTML. This is where you use JS to interact with your CSS and HTML.

*   **Selecting Elements:**
    ```javascript
    const title = document.querySelector('#title');
    const button = document.querySelector('#btn');
    ```
*   **Changing Content:**
    ```javascript
    title.textContent = "JavaScript is awesome!";
    ```
*   **Changing Styles:**
    ```javascript
    title.style.color = "blue";
    title.style.fontSize = "3rem";
    ```

---

### 4. Handling Events
This is how you make your website interactive. You tell JS to "listen" for user actions (clicks, typing, scrolling).

```javascript
const button = document.querySelector('#btn');

button.addEventListener('click', () => {
    document.body.style.backgroundColor = "yellow";
    alert("You clicked the button!");
});
```

---

### 5. Managing CSS Classes
Instead of changing individual styles in JS (which is messy), the best practice is to **toggle CSS classes** that you have already written in your `style.css`.

**CSS:**
```css
.dark-mode {
    background-color: #333;
    color: white;
}
```

**JavaScript:**
```javascript
const button = document.querySelector('#btn');
button.addEventListener('click', () => {
    document.body.classList.toggle('dark-mode');
});
```

---

### 6. Practice Projects (Building Order)
Don't just watch videos; build these small projects in order. Do not use any libraries.

1.  **A Background Color Flipper:** A button that changes the page background color to a random color.
2.  **A Simple Counter:** Buttons to increase, decrease, and reset a number displayed on the screen.
3.  **A To-Do List:** An input field and a "Add" button that creates new `<li>` elements. (This teaches you `document.createElement`).
4.  **A Modal Window:** A pop-up that appears when you click a button and closes when you click an "X".
5.  **Form Validator:** A sign-up form that shows error messages in red if the password is too short.

---

### 7. Essential Modern Concepts (ES6+)
As you get comfortable, focus on these modern features:
*   **Template Literals:** Using backticks `` `Hello ${name}` `` instead of `"Hello " + name`.
*   **Arrow Functions:** `() => { }`.
*   **Arrays Methods:** Learning how to use `.map()`, `.filter()`, and `.forEach()`.
*   **Fetch API:** How to get data from other websites (APIs).

---

### Best Resources for Vanilla JS
*   **[MDN Web Docs](https://developer.mozilla.org/en-US/docs/Web/JavaScript):** The "Bible" of JavaScript. If you forget how a command works, look it up here.
*   **[JavaScript.info](https://javascript.info/):** The best written tutorial for deep explanations.
*   **[Wes Bos - JavaScript 30](https://javascript30.com/):** A free 30-day challenge building 30 things with Vanilla JS. (Highly recommended after you learn the basics).

**Pro Tip:** Open your browser's "Developer Tools" (F12 or Right Click > Inspect) and go to the **Console** tab. You can write and test JavaScript code right there on any website!