---
id: 20260420151929
title: Week One Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp]
---

# Week One Vanilla JavaScript Bootcamp

Perfect — let’s do this properly 👍\
This will feel very similar to your Node.js bootcamp, but now **pure browser + HTML + CSS + JavaScript**.

***

# 🚀 Week 1: Vanilla JavaScript Bootcamp (Browser Only)

## 🎯 Goal of Week 1

You will:

* Understand how JS runs in the browser

* Use Chrome DevTools like a pro

* Learn variables, functions, and basic DOM access

* Build your **first interactive page**

***

# 🗓️ Day 1 — Your First JavaScript in the Browser

## ✅ Task: Create your base project

### `index.html`

```html
<!DOCTYPE html>
<html>
<head>
  <title>Week 1</title>
</head>
<body>

  <h1>Hello JavaScript</h1>

  <script src="script.js"></script>
</body>
</html>
```

### `script.js`

```javascript
console.log("Hello from JavaScript!");
```

***

## 🧠 Learn

* Browser loads HTML → then JS runs

* JS runs **top to bottom**

***

## 🧪 Practice (IMPORTANT)

Open Chrome → Press **F12 → Console**

Try:

```javascript
console.log(2 + 2);
console.log("Karl");
```

***

# 🗓️ Day 2 — Variables & Data Types

## 🧠 Learn

```javascript
let name = "Karl";     // string
let age = 30;          // number
let isHappy = true;    // boolean
```

***

## 🧪 Practice

Add to `script.js`:

```javascript
let city = "Frankfurt";

console.log(city);
console.log(typeof city);
```

***

## 🎯 Mini Task

Create variables for:

* your name

* your favorite color

* your age

Print them.

***

# 🗓️ Day 3 — Functions

## 🧠 Learn

```javascript
function greet() {
  console.log("Hello!");
}

greet();
```

With parameters:

```javascript
function greetUser(name) {
  console.log("Hello " + name);
}

greetUser("Karl");
```

***

## 🧪 Practice

Create:

```javascript
function add(a, b) {
  return a + b;
}

console.log(add(2, 3));
```

***

# 🗓️ Day 4 — The DOM (VERY IMPORTANT 🔥)

This is where JavaScript becomes powerful.

## 🧠 Learn

Update your HTML:

```html
<h1 id="title">Hello</h1>
```

In JS:

```javascript
const title = document.getElementById("title");

console.log(title);
```

***

## 🎯 Modify the page

```javascript
title.textContent = "Hello Karl!";
```

***

## 🧪 Practice

Try:

```javascript
title.style.color = "red";
title.style.fontSize = "40px";
```

***

# 🗓️ Day 5 — Events (User Interaction)

## 🧠 Learn

Update HTML:

```html
<button id="btn">Click me</button>
```

JS:

```javascript
const btn = document.getElementById("btn");

btn.addEventListener("click", function() {
  console.log("Button clicked!");
});
```

***

## 🎯 Make it interactive

```javascript
btn.addEventListener("click", function() {
  document.body.style.backgroundColor = "lightblue";
});
```

***

# 🗓️ Day 6 — Combine Everything

## 🎯 Mini Project: Button Changes Text

### HTML

```html
<h1 id="title">Hello</h1>
<button id="btn">Change Text</button>
```

### JS

```javascript
const title = document.getElementById("title");
const btn = document.getElementById("btn");

btn.addEventListener("click", function() {
  title.textContent = "You clicked the button!";
});
```

***

## 🧪 Bonus Challenge

* Change color too

* Count clicks

***

# 🗓️ Day 7 — First Real Mini Project

## 🎯 Project: Click Counter

### HTML

```html
<h1 id="counter">0</h1>
<button id="btn">Increase</button>
```

### JS

```javascript
let count = 0;

const counter = document.getElementById("counter");
const btn = document.getElementById("btn");

btn.addEventListener("click", function() {
  count++;
  counter.textContent = count;
});
```

***

# 🧠 End of Week 1 — What You Should Know

You can now:

✅ Run JS in browser\
✅ Use DevTools console\
✅ Use variables & functions\
✅ Access HTML with DOM\
✅ React to user actions (events)\
✅ Build small interactive features

***

# 💪 Daily Habit (IMPORTANT)

Every day:

* Open DevTools

* Test things in console

* Break your code → fix it

***

# 🚀 Next Step

Week 2 will level you up:

👉 More DOM (querySelector, classes)\
👉 Input fields\
👉 Forms\
👉 Real UI interactions

***

If you're ready, say:\
👉 **“Week 2 please”**
