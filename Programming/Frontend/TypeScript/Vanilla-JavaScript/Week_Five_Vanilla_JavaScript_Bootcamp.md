---
id: 20260420151540
title: Week Five Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp]
---

# Week Five Vanilla JavaScript Bootcamp

Excellent — now you move from “it works” → **“it’s clean, structured, and persistent”** 🔥
This is where your code starts to look like a real developer’s code.

---

# 🚀 Week 5: Vanilla JavaScript Bootcamp

## (Structure, Reusability, LocalStorage)

---

## 🎯 Goal of Week 5

You will:

* Write **clean, organized code**
* Split logic into **functions**
* Understand **separation of concerns**
* Store data in the browser using **localStorage**
* Upgrade your To-Do App to **persistent state**

---

# 🗓️ Day 1 — Clean Code & Functions

## 🧠 Problem (current code)

You probably have:

```javascript
btn.addEventListener("click", function() {
  const li = document.createElement("li");
  li.textContent = input.value;
  list.appendChild(li);
});
```

👉 This gets messy fast.

---

## ✅ Solution: Functions

```javascript
function createTaskElement(text) {
  const li = document.createElement("li");
  li.textContent = text;
  return li;
}
```

```javascript
function addTaskToUI(text) {
  const li = createTaskElement(text);
  list.appendChild(li);
}
```

---

## 🎯 Task

Refactor your code into:

* `createTaskElement`
* `addTaskToUI`
* `handleAddClick`

---

# 🗓️ Day 2 — Separation of Concerns 🧠

## 🔥 VERY IMPORTANT CONCEPT

Split your app into:

| Part  | Responsibility    |
| ----- | ----------------- |
| Data  | tasks array       |
| Logic | add/remove/toggle |
| UI    | DOM rendering     |

---

## 🧪 Example

```javascript
let tasks = [];

function addTask(text) {
  tasks.push({ text, done: false });
  render();
}
```

👉 UI is NOT modified directly here.

---

# 🗓️ Day 3 — LocalStorage (Game Changer 💾)

## 🧠 Learn

Browser storage:

```javascript
localStorage.setItem("name", "Karl");
localStorage.getItem("name");
```

---

## ⚠️ Important

localStorage only stores **strings**

---

## ✅ Store array

```javascript
localStorage.setItem("tasks", JSON.stringify(tasks));
```

---

## ✅ Load array

```javascript
const saved = JSON.parse(localStorage.getItem("tasks")) || [];
tasks = saved;
```

---

# 🗓️ Day 4 — Save Your To-Do App

## 🎯 Goal

Your tasks persist after refresh

---

## 🔧 Update your logic

```javascript
function saveTasks() {
  localStorage.setItem("tasks", JSON.stringify(tasks));
}
```

---

```javascript
function addTask(text) {
  tasks.push({ text, done: false });
  saveTasks();
  render();
}
```

---

```javascript
function loadTasks() {
  const saved = JSON.parse(localStorage.getItem("tasks")) || [];
  tasks = saved;
}
```

---

## 🎯 On page load

```javascript
loadTasks();
render();
```

---

# 🗓️ Day 5 — Better Rendering Structure

## 🧠 Improve `render()`

```javascript
function render() {
  list.innerHTML = "";

  tasks.forEach(function(task, index) {
    const li = document.createElement("li");
    li.textContent = task.text;

    if (task.done) {
      li.classList.add("done");
    }

    li.addEventListener("click", function() {
      toggleTask(index);
    });

    list.appendChild(li);
  });
}
```

---

## 🎯 Add toggle function

```javascript
function toggleTask(index) {
  tasks[index].done = !tasks[index].done;
  saveTasks();
  render();
}
```

---

# 🗓️ Day 6 — Delete & Clean UI

## 🎯 Delete by index (better!)

```javascript
function deleteTask(index) {
  tasks.splice(index, 1);
  saveTasks();
  render();
}
```

---

## 🧪 Button inside render

```javascript
const deleteBtn = document.createElement("button");
deleteBtn.textContent = "X";

deleteBtn.addEventListener("click", function(e) {
  e.stopPropagation();
  deleteTask(index);
});
```

---

# 🗓️ Day 7 — Final Project (Week 5)

## 🎯 Build a **Persistent To-Do App**

### Features:

✅ Add task
✅ Delete task
✅ Toggle done
✅ Save to localStorage
✅ Load on refresh
✅ Clean structure (functions!)

---

# 🧠 Final Architecture (IMPORTANT)

Your app should look like this mentally:

```text
DATA (tasks array)
   ↓
LOGIC (add, delete, toggle)
   ↓
RENDER (update DOM)
   ↓
STORAGE (localStorage)
```

---

# 💡 Bonus Upgrades

### 🧹 Clear all tasks

```javascript
function clearAll() {
  tasks = [];
  saveTasks();
  render();
}
```

---

### 🔢 Task counter

```javascript
document.querySelector("#count").textContent = tasks.length;
```

---

### 🚫 Prevent empty input

```javascript
if (!text.trim()) return;
```

---

# 🧠 End of Week 5 — You Now Think Like a Developer

🔥 Structured code
🔥 Separation of concerns
🔥 Persistent data
🔥 Real app architecture
🔥 Maintainable JavaScript

---

# 💪 Practice Ideas

Build:

* 📝 Notes app (with save)
* 📚 Bookmark list
* 🎯 Habit tracker

---

# 🚀 Week 6 Preview (Big Step)

Now we go into **professional JavaScript concepts**:

👉 Modules (split files)
👉 Better project structure
👉 Reusable utilities
👉 Intro to architecture patterns

---

If you're ready:

👉 **“Week 6 please”**
