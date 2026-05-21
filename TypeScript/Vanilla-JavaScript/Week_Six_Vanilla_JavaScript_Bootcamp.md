---
id: 20260420153830
title: Week Six Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp]
---

# Week Six Vanilla JavaScript Bootcamp

Perfect — now you’re stepping into **“professional JavaScript structure”** 🚀\
This is where your projects stop being single files and start looking like real applications.

***

# 🚀 Week 6: Vanilla JavaScript Bootcamp

## (Modules, File Structure, Scalable Code)

***

## 🎯 Goal of Week 6

You will:

* Split code into **multiple files**

* Use **ES Modules (`import` / `export`)**

* Organize your app like a real project

* Write **reusable utilities**

* Improve your To-Do App structure

***

# 🗓️ Day 1 — Why Modules?

## 🧠 Problem

Right now everything is in:

```text
script.js 😱
```

👉 This becomes:

* messy

* hard to maintain

* impossible to scale

***

## ✅ Solution: Modules

Split code into files:

```text
app/
  main.js
  data.js
  ui.js
  storage.js
```

***

# 🗓️ Day 2 — ES Modules (IMPORTANT 🔥)

## 🧠 Enable modules in HTML

```html
<script type="module" src="main.js"></script>
```

***

## 🧪 Example

### `math.js`

```javascript
export function add(a, b) {
  return a + b;
}
```

***

### `main.js`

```javascript
import { add } from "./math.js";

console.log(add(2, 3));
```

***

## ⚠️ Important Rules

* Use `./` for local files

* File extension **required** (`.js`)

* Works directly in Chrome ✅

***

# 🗓️ Day 3 — Refactor Your To-Do App

## 🎯 Split responsibilities

***

### `data.js`

```javascript
export let tasks = [];

export function setTasks(newTasks) {
  tasks = newTasks;
}
```

***

### `storage.js`

```javascript
export function saveTasks(tasks) {
  localStorage.setItem("tasks", JSON.stringify(tasks));
}

export function loadTasks() {
  return JSON.parse(localStorage.getItem("tasks")) || [];
}
```

***

### `ui.js`

```javascript
export function render(tasks, onToggle, onDelete) {
  const list = document.querySelector("#list");
  list.innerHTML = "";

  tasks.forEach((task, index) => {
    const li = document.createElement("li");
    li.textContent = task.text;

    if (task.done) li.classList.add("done");

    li.addEventListener("click", () => onToggle(index));

    const btn = document.createElement("button");
    btn.textContent = "X";

    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      onDelete(index);
    });

    li.appendChild(btn);
    list.appendChild(li);
  });
}
```

***

# 🗓️ Day 4 — Main Controller (Glue Code)

## 🧠 `main.js`

```javascript
import { tasks, setTasks } from "./data.js";
import { saveTasks, loadTasks } from "./storage.js";
import { render } from "./ui.js";

setTasks(loadTasks());

function addTask(text) {
  tasks.push({ text, done: false });
  saveTasks(tasks);
  updateUI();
}

function toggleTask(index) {
  tasks[index].done = !tasks[index].done;
  saveTasks(tasks);
  updateUI();
}

function deleteTask(index) {
  tasks.splice(index, 1);
  saveTasks(tasks);
  updateUI();
}

function updateUI() {
  render(tasks, toggleTask, deleteTask);
}

document.querySelector("#btn").addEventListener("click", () => {
  const input = document.querySelector("#input");
  addTask(input.value);
  input.value = "";
});

updateUI();
```

***

# 🗓️ Day 5 — Reusable Utilities 🧰

## 🧠 Create `utils.js`

```javascript
export function isEmpty(text) {
  return !text || !text.trim();
}
```

***

## 🎯 Use it

```javascript
import { isEmpty } from "./utils.js";

if (isEmpty(input.value)) return;
```

***

# 🗓️ Day 6 — Folder Structure (Real Project Feel)

## 🧠 Organize like this:

```text
project/
  index.html
  css/
    style.css
  js/
    main.js
    data.js
    ui.js
    storage.js
    utils.js
```

***

## 🎯 Update import paths

```javascript
import { render } from "./ui.js"; // if same folder
```

***

# 🗓️ Day 7 — Final Project (Week 6)

## 🎯 Modular To-Do App

### Features:

✅ Clean file structure\
✅ Modules (`import/export`)\
✅ Persistent storage\
✅ UI separated from logic\
✅ Reusable utilities

***

# 🧠 Key Concept (VERY IMPORTANT)

You now think in **layers**:

```text
UI (ui.js)
LOGIC (main.js)
DATA (data.js)
STORAGE (storage.js)
UTILS (utils.js)
```

👉 This is how real apps are built.

***

# 💡 Bonus Upgrades

### ⌨️ Press Enter to add task

```javascript
input.addEventListener("keypress", (e) => {
  if (e.key === "Enter") addTask(input.value);
});
```

***

### 📦 Default tasks (first load)

```javascript
if (tasks.length === 0) {
  tasks.push({ text: "Start learning JS", done: false });
}
```

***

# 🧠 End of Week 6 — You Are Now Doing Real Development

🔥 Modules & file structure\
🔥 Separation of concerns (advanced)\
🔥 Reusable utilities\
🔥 Scalable architecture\
🔥 Clean, maintainable code

***

# 🚀 Week 7 Preview (Advanced Browser Power)

Now things get even more powerful:

👉 Event delegation (performance)\
👉 Advanced DOM patterns\
👉 More complex UI interactions\
👉 Keyboard + UX improvements

***

If you're ready:

👉 **“Week 7 please”**
