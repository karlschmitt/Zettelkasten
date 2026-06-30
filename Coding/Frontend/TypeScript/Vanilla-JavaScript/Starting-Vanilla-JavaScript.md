---
id: 20260420152235
title: Starting Vanilla JavaScript
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript]
---

# Starting Vanilla JavaScript

Great question — this is actually the **best way to learn JavaScript first**: plain (“vanilla”) JS running directly in the browser with HTML + CSS. No build tools, no Node.js — just you and Chrome.

Let’s build you a **clear, structured learning path** 👍

***

# 🧠 1. Understand the Big Picture

In a browser:

* **HTML** → structure (the skeleton)

* **CSS** → styling (the looks)

* **JavaScript** → behavior (the brain)

👉 JavaScript interacts with the page via something called the **DOM (Document Object Model)**.

***

# 🛠️ 2. Your Setup (Super Simple)

You only need:

* Chrome (or any browser)

* A text editor (VS Code, Notepad, whatever)

Create this file:

### `index.html`

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>JS Learning</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>

  <h1 id="title">Hello World</h1>
  <button id="btn">Click me</button>

  <script src="script.js"></script>
</body>
</html>
```

### `style.css`

```css
body {
  font-family: Arial;
  text-align: center;
  margin-top: 50px;
}

h1 {
  color: blue;
}
```

### `script.js`

```javascript
console.log("JavaScript is working!");
```

👉 Open `index.html` in Chrome\
👉 Press **F12 → Console**

***

# 🔍 3. Learn the Chrome DevTools (VERY important)

You’ll use:

* **Console** → test JavaScript

* **Elements** → inspect HTML

* **Sources** → debug code

Try this in the console:

```javascript
document.querySelector("h1")
```

***

# 📚 4. Core JavaScript (Browser Context)

Learn these basics first:

### Variables

```javascript
let name = "Karl";
const age = 30;
```

### Functions

```javascript
function greet() {
  console.log("Hello!");
}
```

### Events (SUPER IMPORTANT)

```javascript
document.getElementById("btn").addEventListener("click", function() {
  alert("Button clicked!");
});
```

***

# 🌐 5. DOM Manipulation (THIS is the core skill)

Change HTML with JavaScript:

```javascript
const title = document.getElementById("title");

title.textContent = "New Text!";
title.style.color = "red";
```

***

# 🎯 6. Mini Projects (Best Way to Learn)

Start simple and build up:

### 🟢 Beginner

* Button click counter

* Change background color

* Show/hide text

### 🟡 Intermediate

* To-do list

* Form validation

* Light/Dark mode toggle

### 🔴 Advanced (still browser-only)

* Weather app (using fetch)

* Notes app with localStorage

* Quiz app

***

# 🔌 7. Learn Browser APIs

These are built into Chrome:

### Fetch API (HTTP requests)

```javascript
fetch("https://api.github.com")
  .then(res => res.json())
  .then(data => console.log(data));
```

### Local Storage

```javascript
localStorage.setItem("name", "Karl");
console.log(localStorage.getItem("name"));
```

***

# 🧩 8. Suggested Learning Path (4 Weeks)

### Week 1 — Basics

* Variables, functions, console

* Simple DOM selection

### Week 2 — Interaction

* Events (click, input)

* Modify HTML & CSS

### Week 3 — Logic + Data

* Arrays & objects

* Loops

* Build a to-do list

### Week 4 — Real Apps

* Fetch API

* Local storage

* Small project (weather, notes)

***

# ⚡ 9. Practice Workflow (VERY IMPORTANT)

Do this every day:

1. Write small code

2. Open in browser

3. Use DevTools

4. Break things → fix them

***

# 💡 10. Golden Rules

* Don’t memorize — **build**

* Use `console.log()` a lot

* Read errors (they help you!)

* Keep projects small

***

# 🚀 If you want…

I can turn this into a **structured bootcamp (like your Node.js one)**:

👉 Week-by-week\
👉 With exercises\
👉 Using ONLY:

* HTML

* CSS

* Vanilla JS

* Chrome DevTools

Just say:\
**“Yes, give me Week 1 Vanilla JS Bootcamp”**
