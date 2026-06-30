---
id: 20260420152715
title: Week Three Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp]
---

# Week Three Vanilla JavaScript Bootcamp

Awesome — Week 3 is where you go from “UI tinkering” to **real programming + app logic** 💪\
This is the step that separates beginners from developers.

***

# 🚀 Week 3: Vanilla JavaScript Bootcamp (Logic, Arrays, Real Apps)

## 🎯 Goal of Week 3

You will:

* Think like a programmer (logic!)

* Use **arrays & objects**

* Work with **loops**

* Structure your code better

* Build a **real to-do app (data-driven)**

***

# 🗓️ Day 1 — Arrays (Core Data Structure)

## 🧠 Learn

```javascript
let fruits = ["apple", "banana", "orange"];
```

Access:

```javascript
console.log(fruits[0]); // apple
```

***

## 🔧 Useful methods

```javascript
fruits.push("grape");     // add
fruits.pop();             // remove last
fruits.length;            // size
```

***

## 🧪 Practice

```javascript
let tasks = ["Learn JS", "Drink coffee"];

tasks.push("Build app");

console.log(tasks);
```

***

## 🎯 Task

Loop through array:

```javascript
tasks.forEach(function(task) {
  console.log(task);
});
```

***

# 🗓️ Day 2 — Objects (Structured Data)

## 🧠 Learn

```javascript
let user = {
  name: "Karl",
  age: 30,
  isAdmin: false
};
```

Access:

```javascript
console.log(user.name);
```

***

## 🧪 Practice

```javascript
let task = {
  text: "Learn JavaScript",
  done: false
};
```

***

## 🎯 Task

Create an array of objects:

```javascript
let tasks = [
  { text: "Learn JS", done: false },
  { text: "Build app", done: true }
];
```

***

# 🗓️ Day 3 — Loops + Logic

## 🧠 Learn

### `forEach`

```javascript
tasks.forEach(function(task) {
  console.log(task.text);
});
```

***

### `if` conditions

```javascript
if (task.done) {
  console.log("Completed");
}
```

***

## 🧪 Practice

```javascript
tasks.forEach(function(task) {
  if (task.done) {
    console.log(task.text + " ✅");
  } else {
    console.log(task.text + " ❌");
  }
});
```

***

# 🗓️ Day 4 — Connect Data to the DOM 🔥

Now it gets powerful.

## 🎯 Goal

Render array → HTML

***

### HTML

```html
<ul id="list"></ul>
```

***

### JS

```javascript
const list = document.querySelector("#list");

let tasks = [
  { text: "Learn JS", done: false },
  { text: "Build app", done: true }
];

function render() {
  list.innerHTML = "";

  tasks.forEach(function(task) {
    const li = document.createElement("li");
    li.textContent = task.text;

    if (task.done) {
      li.style.textDecoration = "line-through";
    }

    list.appendChild(li);
  });
}

render();
```

***

# 🗓️ Day 5 — Update Data (Real App Behavior)

## 🎯 Add new tasks to array

```javascript
function addTask(text) {
  tasks.push({ text: text, done: false });
  render();
}
```

***

## 🧪 Connect with input

```javascript
const input = document.querySelector("#input");
const btn = document.querySelector("#btn");

btn.addEventListener("click", function() {
  addTask(input.value);
  input.value = "";
});
```

***

# 🗓️ Day 6 — Toggle + Delete (Real App 🔥🔥)

## 🎯 Toggle done

Inside `render()`:

```javascript
li.addEventListener("click", function() {
  task.done = !task.done;
  render();
});
```

***

## 🎯 Delete task

```javascript
const deleteBtn = document.createElement("button");
deleteBtn.textContent = "X";

deleteBtn.addEventListener("click", function(event) {
  event.stopPropagation(); // IMPORTANT
  tasks = tasks.filter(t => t !== task);
  render();
});

li.appendChild(deleteBtn);
```

***

# 🗓️ Day 7 — Final Project (Week 3)

## 🎯 Build a REAL To-Do App

Features:

✅ Add task\
✅ Delete task\
✅ Mark as done\
✅ Re-render UI\
✅ Data-driven (array of objects)

***

## 🧠 Key Concept (VERY IMPORTANT)

👉 **Data → UI**

You are no longer just changing HTML manually.

You are:

* storing data in JS

* rendering UI from that data

This is how frameworks like React work 👀

***

# 💡 Bonus (If You Want to Level Up)

### Filter tasks

```javascript
let completed = tasks.filter(task => task.done);
```

***

### Count tasks

```javascript
let count = tasks.length;
```

***

# 🧠 End of Week 3 — You Now Understand

🔥 Arrays & objects\
🔥 Loops & conditions\
🔥 Data-driven UI\
🔥 Re-rendering logic\
🔥 Real app structure

***

# 💪 Practice Ideas

Build:

* 📝 Better To-Do (with counter)

* 🧹 “Clear completed” button

* 🔍 Filter (all / done / active)

***

# 🚀 Week 4 Preview

Now we go from “local apps” → “real web apps”:

👉 Fetch API (real data from internet)\
👉 Async JavaScript (promises)\
👉 JSON data\
👉 Build a **Weather App 🌦️**

***

If you're ready:

👉 **“Week 4 please”**
