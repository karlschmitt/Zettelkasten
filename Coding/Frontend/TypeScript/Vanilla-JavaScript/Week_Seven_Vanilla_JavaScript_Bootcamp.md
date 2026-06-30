---
id: 20260420154458
title: Week Seven Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp, DOM]
---

# Week Seven Vanilla JavaScript Bootcamp

Now you’re entering **advanced frontend territory** 🔥\
Week 7 is where you stop writing “working code” and start writing **smart, scalable, performant code**.

***

# 🚀 Week 7: Vanilla JavaScript Bootcamp

## (Advanced DOM, Event Delegation, UX Power)

***

## 🎯 Goal of Week 7

You will:

* Master **event delegation** (VERY important 🔥)

* Improve performance & scalability

* Handle **keyboard input**

* Build smoother **user experience (UX)**

* Upgrade your To-Do App to a **pro-level UI**

***

# 🗓️ Day 1 — The Problem with Many Event Listeners

## 🧠 Current approach (bad for scale)

```javascript
tasks.forEach((task, index) => {
  const li = document.createElement("li");

  li.addEventListener("click", () => {
    toggleTask(index);
  });
});
```

👉 Problem:

* Creates MANY listeners

* Slower with big lists

* Harder to manage

***

# 🗓️ Day 2 — Event Delegation (GAME CHANGER 🚀)

## 🧠 Idea

👉 Put **ONE listener on the parent**

***

### HTML

```html
<ul id="list"></ul>
```

***

### JS

```javascript
const list = document.querySelector("#list");

list.addEventListener("click", function(event) {
  console.log(event.target);
});
```

***

## 🎯 Detect clicked item

```javascript
list.addEventListener("click", function(event) {
  if (event.target.tagName === "LI") {
    console.log("List item clicked");
  }
});
```

***

# 🗓️ Day 3 — Use Data Attributes (SUPER IMPORTANT)

## 🧠 Store index in HTML

```javascript
li.dataset.index = index;
```

***

## 🎯 Use it

```javascript
list.addEventListener("click", function(event) {
  const index = event.target.dataset.index;

  if (index !== undefined) {
    toggleTask(index);
  }
});
```

***

## 💡 Why this is powerful

* No closures needed

* Cleaner code

* Works for dynamic elements

***

# 🗓️ Day 4 — Handle Delete with Delegation

## 🎯 Add delete button

```javascript
const btn = document.createElement("button");
btn.textContent = "X";
btn.dataset.index = index;
btn.classList.add("delete");
```

***

## 🧠 Handle both click types

```javascript
list.addEventListener("click", function(event) {
  const index = event.target.dataset.index;

  if (event.target.classList.contains("delete")) {
    deleteTask(index);
    return;
  }

  if (event.target.tagName === "LI") {
    toggleTask(index);
  }
});
```

***

# 🗓️ Day 5 — Keyboard & UX Improvements ⌨️

## 🎯 Add Enter key support

```javascript
input.addEventListener("keydown", function(event) {
  if (event.key === "Enter") {
    addTask(input.value);
    input.value = "";
  }
});
```

***

## 🎯 Auto-focus input

```javascript
input.focus();
```

***

## 🎯 Prevent empty tasks

```javascript
if (!input.value.trim()) return;
```

***

# 🗓️ Day 6 — Better UI Feedback

## 🎯 Add hover effect (CSS)

```css
li:hover {
  background: #eee;
  cursor: pointer;
}
```

***

## 🎯 Highlight active tasks

```css
li.done {
  opacity: 0.6;
}
```

***

## 🎯 Show empty state

```javascript
if (tasks.length === 0) {
  list.innerHTML = "<p>No tasks yet</p>";
}
```

***

# 🗓️ Day 7 — Final Project (Week 7)

## 🎯 Pro-Level To-Do App

### Features:

✅ Event delegation (1 listener only)\
✅ Data attributes (`data-index`)\
✅ Keyboard support (Enter key)\
✅ Clean UX (hover, focus)\
✅ Empty state handling\
✅ Fast & scalable

***

# 🧠 Key Concept (VERY IMPORTANT)

👉 **Control the parent, not the children**

Instead of:

```text
many listeners ❌
```

You now use:

```text
one smart listener ✅
```

***

# 💡 Bonus Upgrades

### 🔍 Filter buttons (All / Done / Active)

```javascript
const activeTasks = tasks.filter(t => !t.done);
```

***

### 🔢 Show remaining tasks

```javascript
const remaining = tasks.filter(t => !t.done).length;
```

***

### 🧹 Clear completed

```javascript
tasks = tasks.filter(t => !t.done);
```

***

# 🧠 End of Week 7 — You Are Now Advanced

🔥 Event delegation\
🔥 Scalable DOM handling\
🔥 Clean UX improvements\
🔥 Keyboard interaction\
🔥 Performance-aware coding

***

# 🚀 Week 8 Preview (Final Level)

Now you reach **expert-level fundamentals**:

👉 Debouncing & throttling\
👉 Performance optimization\
👉 Code patterns (MVC-like thinking)\
👉 Polishing real apps

***

If you're ready:

👉 **“Week 8 please”**
