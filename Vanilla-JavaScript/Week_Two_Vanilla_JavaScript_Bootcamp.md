---
id: 20260420152514
title: Week Two Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
---

# Week Two Vanilla JavaScript Bootcamp

Nice — now it gets really fun. Week 2 is where things start to feel like _real apps_ 💪

***

# 🚀 Week 2: Vanilla JavaScript Bootcamp (Interactivity & UI)

## 🎯 Goal of Week 2

You will:

* Select elements like a pro (`querySelector`)

* Work with **multiple elements**

* Handle **user input**

* Build real UI features (toggle, form, list)

***

# 🗓️ Day 1 — `querySelector` (Modern DOM)

## 🧠 Learn

Instead of:

```javascript
document.getElementById("title");
```

Use:

```javascript
document.querySelector("#title");   // id
document.querySelector(".item");    // class
document.querySelector("h1");       // tag
```

***

## 🧪 Practice

HTML:

```html
<h1 id="title">Hello</h1>
<p class="text">Paragraph</p>
```

JS:

```javascript
const title = document.querySelector("#title");
const text = document.querySelector(".text");

console.log(title, text);
```

***

## 🎯 Task

Change both elements:

```javascript
title.textContent = "Changed!";
text.style.color = "green";
```

***

# 🗓️ Day 2 — Multiple Elements

## 🧠 Learn

```javascript
const items = document.querySelectorAll(".item");
```

This returns a list.

***

## 🧪 Practice

HTML:

```html
<ul>
  <li class="item">One</li>
  <li class="item">Two</li>
  <li class="item">Three</li>
</ul>
```

JS:

```javascript
const items = document.querySelectorAll(".item");

items.forEach(function(item) {
  console.log(item.textContent);
});
```

***

## 🎯 Task

Make all items red:

```javascript
items.forEach(function(item) {
  item.style.color = "red";
});
```

***

# 🗓️ Day 3 — Input Fields (User Data)

## 🧠 Learn

HTML:

```html
<input id="nameInput" type="text" placeholder="Enter name">
<button id="btn">Submit</button>
```

JS:

```javascript
const input = document.querySelector("#nameInput");
const btn = document.querySelector("#btn");

btn.addEventListener("click", function() {
  console.log(input.value);
});
```

***

## 🎯 Task

Show input on page:

```html
<p id="output"></p>
```

```javascript
const output = document.querySelector("#output");

btn.addEventListener("click", function() {
  output.textContent = input.value;
});
```

***

# 🗓️ Day 4 — CSS Classes (Better than inline styles)

## 🧠 Learn

CSS:

```css
.dark {
  background-color: black;
  color: white;
}
```

JS:

```javascript
document.body.classList.add("dark");
document.body.classList.remove("dark");
document.body.classList.toggle("dark");
```

***

## 🎯 Task — Dark Mode Toggle

HTML:

```html
<button id="toggle">Toggle Dark Mode</button>
```

JS:

```javascript
const toggle = document.querySelector("#toggle");

toggle.addEventListener("click", function() {
  document.body.classList.toggle("dark");
});
```

***

# 🗓️ Day 5 — Creating Elements (Dynamic UI 🔥)

## 🧠 Learn

```javascript
const li = document.createElement("li");
li.textContent = "New Item";

document.body.appendChild(li);
```

***

## 🧪 Practice

Add to a list:

```html
<ul id="list"></ul>
```

```javascript
const list = document.querySelector("#list");

const li = document.createElement("li");
li.textContent = "Item 1";

list.appendChild(li);
```

***

# 🗓️ Day 6 — Mini Project: Simple To-Do List

## 🎯 Goal

User types → clicks → item appears

***

### HTML

```html
<input id="taskInput" type="text">
<button id="addBtn">Add</button>

<ul id="taskList"></ul>
```

***

### JS

```javascript
const input = document.querySelector("#taskInput");
const button = document.querySelector("#addBtn");
const list = document.querySelector("#taskList");

button.addEventListener("click", function() {
  const li = document.createElement("li");
  li.textContent = input.value;

  list.appendChild(li);

  input.value = ""; // clear input
});
```

***

## 🧪 Bonus

* Prevent empty input

* Add delete button per item

***

# 🗓️ Day 7 — Improve Your To-Do App

## 🎯 Add Features

### 1. Delete button

```javascript
const deleteBtn = document.createElement("button");
deleteBtn.textContent = "X";

deleteBtn.addEventListener("click", function() {
  li.remove();
});

li.appendChild(deleteBtn);
```

***

### 2. Mark as done

```javascript
li.addEventListener("click", function() {
  li.classList.toggle("done");
});
```

CSS:

```css
.done {
  text-decoration: line-through;
}
```

***

# 🧠 End of Week 2 — What You Can Do Now

You can now:

✅ Select any element (`querySelector`)\
✅ Work with multiple elements\
✅ Handle user input\
✅ Toggle styles with classes\
✅ Create & delete elements\
✅ Build a real UI (To-Do App!)

***

# 💪 Practice Like a Pro

Try building:

* 🌓 Dark mode toggle (polished)

* 📝 To-do list with delete + done

* 🎨 Color picker (input → background)

***

# 🚀 Next Level (Week 3)

We’ll go deeper into **real programming**:

👉 Arrays & objects\
👉 Loops & logic\
👉 Better app structure\
👉 Real-world data handling

***

If you're ready:

👉 **“Week 3 please”**
