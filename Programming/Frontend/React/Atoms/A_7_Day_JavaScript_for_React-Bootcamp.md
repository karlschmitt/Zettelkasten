---
id: 20260508193854 
title: A 7-Day JavaScript for React Bootcamp
author: Karl Schmitt
date: 2026-05-08
keywords: [ React, JavaScript]
---

# A **7-Day JavaScript for React Bootcamp**

## ⚛️ 7-Day JavaScript for React Bootcamp

This bootcamp is designed to prepare you for modern React development using:

* Modern JavaScript (ES6+)
* Browser-based development
* Small practical projects
* React-focused thinking

You do **not** need:

* Node.js mastery
* Advanced algorithms
* TypeScript yet

Goal after 7 days:

✅ Understand React-oriented JavaScript
✅ Build mini apps comfortably
✅ Read React tutorials without confusion
✅ Be ready for components, hooks, and state

---

# 🧰 Setup

Use:

* Chrome or Edge
* VS Code
* Browser DevTools
* Optional local server

Useful extension:

* Live Server

---

# 📅 Day 1 — Variables, Functions & Modern Syntax

---

# 🎯 Goals

Learn:

* `const` and `let`
* Arrow functions
* Template literals
* Basic arrays & objects

---

# 📘 Topics

---

## 1. Variables

```javascript id="pf03xq"
const appName = "React Bootcamp";
let count = 0;

count++;
```

---

## 2. Strings & Template Literals

```javascript id="ecjlwm"
const user = "Karl";

console.log(`Hello ${user}`);
```

---

## 3. Functions

Traditional:

```javascript id="ewjzj8"
function greet(name) {
  return `Hello ${name}`;
}
```

Arrow:

```javascript id="s0onmb"
const greet = (name) => {
  return `Hello ${name}`;
};
```

Short version:

```javascript id="38o3s2"
const greet = name => `Hello ${name}`;
```

---

## 4. Arrays

```javascript id="0jxjlwm"
const colors = ["red", "green", "blue"];
```

---

## 5. Objects

```javascript id="v05gxv"
const user = {
  name: "Karl",
  age: 30
};
```

---

# 🛠️ Exercises

1. Create a user object
2. Create an array of hobbies
3. Write a greeting function
4. Loop through hobbies

---

# 🚀 Mini Project

## Profile Card

Create:

* name
* age
* hobbies
* render them into HTML

Use:

* template literals
* objects
* arrays

---

# 📅 Day 2 — Arrays & React-Critical Methods

---

# 🎯 Goals

Master:

* `map()`
* `filter()`
* `find()`
* `forEach()`

These are ESSENTIAL for React rendering.

---

# 📘 Topics

---

# 1. `map()`

MOST IMPORTANT.

```javascript id="fwcuhm"
const numbers = [1, 2, 3];

const doubled = numbers.map(n => n * 2);
```

React uses this constantly:

```jsx id="8q5hyc"
users.map(user => <li>{user.name}</li>)
```

---

# 2. `filter()`

```javascript id="w9tv2z"
const activeUsers =
  users.filter(user => user.active);
```

---

# 3. `find()`

```javascript id="9e97pd"
const user =
  users.find(user => user.id === 2);
```

---

# 4. `forEach()`

```javascript id="m4q8ww"
users.forEach(user => {
  console.log(user.name);
});
```

---

# 🛠️ Exercises

1. Double numbers with `map`
2. Filter active users
3. Find one user
4. Render array data into HTML

---

# 🚀 Mini Project

## User Directory

Features:

* Array of users
* Render user cards
* Filter active users
* Search users

---

# 📅 Day 3 — Destructuring, Spread & Immutability

---

# 🎯 Goals

Learn the syntax React developers use constantly.

---

# 📘 Topics

---

# 1. Object Destructuring

```javascript id="9gsj2z"
const user = {
  name: "Karl",
  age: 30
};

const { name, age } = user;
```

---

# 2. Array Destructuring

```javascript id="9zsjv6"
const colors = ["red", "green"];

const [first, second] = colors;
```

React hooks:

```javascript id="2b0nva"
const [count, setCount] = useState(0);
```

---

# 3. Spread Operator

## Arrays

```javascript id="7bte2c"
const numbers = [1, 2];

const updated = [...numbers, 3];
```

## Objects

```javascript id="u4ydbn"
const updatedUser = {
  ...user,
  age: 31
};
```

---

# 4. Immutability

❌ Bad:

```javascript id="3zddof"
user.name = "Anna";
```

✅ Good:

```javascript id="xyk3eh"
const updatedUser = {
  ...user,
  name: "Anna"
};
```

---

# 🛠️ Exercises

1. Copy arrays
2. Merge objects
3. Update object fields immutably
4. Destructure nested objects

---

# 🚀 Mini Project

## Todo App Data Layer

Features:

* Add todo
* Remove todo
* Toggle complete
* Immutable updates only

---

# 📅 Day 4 — DOM Manipulation & Events

---

# 🎯 Goals

Understand what React replaces.

---

# 📘 Topics

---

# 1. Selecting Elements

```javascript id="4jicrz"
const button =
  document.querySelector("button");
```

---

# 2. Event Listeners

```javascript id="f20sqo"
button.addEventListener("click", () => {
  console.log("Clicked");
});
```

---

# 3. Updating HTML

```javascript id="ygn4p2"
const app =
  document.querySelector("#app");

app.innerHTML = `
  <h1>Hello React Prep</h1>
`;
```

---

# 4. Form Inputs

```javascript id="z4m68w"
input.addEventListener("input", event => {
  console.log(event.target.value);
});
```

---

# 🛠️ Exercises

1. Counter button
2. Live text preview
3. Todo input
4. Dark/light toggle

---

# 🚀 Mini Project

## Interactive Todo App

Features:

* Add todos
* Delete todos
* Mark complete
* Render dynamically

---

# 📅 Day 5 — Async JavaScript & APIs

---

# 🎯 Goals

Prepare for React data fetching.

---

# 📘 Topics

---

# 1. Promises

```javascript id="b0e5sz"
fetch("https://jsonplaceholder.typicode.com/users")
  .then(response => response.json())
  .then(data => console.log(data));
```

---

# 2. Async/Await

```javascript id="1vft9g"
const loadUsers = async () => {
  const response = await fetch(
    "https://jsonplaceholder.typicode.com/users"
  );

  const users = await response.json();

  console.log(users);
};
```

---

# 3. Error Handling

```javascript id="6cwqmr"
try {
  const response = await fetch(url);
} catch (error) {
  console.error(error);
}
```

---

# 🛠️ Exercises

1. Fetch users
2. Render user cards
3. Add loading message
4. Add error handling

---

# 🚀 Mini Project

## API User Explorer

Features:

* Fetch API users
* Search users
* Filter users
* Loading spinner

---

# 📅 Day 6 — Modules & Project Structure

---

# 🎯 Goals

Learn how React projects organize code.

---

# 📘 Topics

---

# 1. Export

```javascript id="ytv9ud"
export const add = (a, b) => a + b;
```

---

# 2. Import

```javascript id="h5znp0"
import { add } from "./math.js";
```

---

# 3. Multiple Files

Example:

```text
src/
 ├── main.js
 ├── users.js
 ├── api.js
 └── ui.js
```

---

# 4. Separation of Concerns

Split:

* API logic
* UI rendering
* state/data
* utility functions

---

# 🛠️ Exercises

1. Create utility module
2. Split todo app into files
3. Create API module
4. Import/export functions

---

# 🚀 Mini Project

## Modular Notes App

Features:

* Separate files
* Render notes
* Save state
* Clean structure

---

# 📅 Day 7 — React Preparation Day

---

# 🎯 Goals

Think like React before learning React.

---

# 📘 Topics

---

# 1. Components as Functions

React:

```jsx id="a9t0op"
function Button() {
  return <button>Click</button>;
}
```

Equivalent thinking:

```javascript id="ph97lt"
const Button = () => {
  return `
    <button>Click</button>
  `;
};
```

---

# 2. Rendering Lists

```jsx id="zwjlwm"
users.map(user =>
  <li>{user.name}</li>
)
```

---

# 3. State Thinking

```javascript id="m25tz6"
let count = 0;

const increment = () => {
  count++;
  render();
};
```

---

# 4. Props Thinking

```javascript id="vmljlwm"
const ProfileCard = (user) => {
  return `
    <h2>${user.name}</h2>
  `;
};
```

---

# 🛠️ Exercises

1. Build fake “components”
2. Pass data into functions
3. Re-render UI manually
4. Render arrays dynamically

---

# 🚀 Final Project

## Mini React Simulation App

Build:

* Component-like functions
* State variables
* Render functions
* Dynamic lists
* Event handling
* API fetching

---

# 🏁 End-of-Bootcamp Skills Checklist

You should now be comfortable with:

| Skill             | Ready? |
| ----------------- | ------ |
| Arrow functions   | ✅      |
| Arrays & objects  | ✅      |
| `map()`           | ✅      |
| Destructuring     | ✅      |
| Spread operator   | ✅      |
| DOM events        | ✅      |
| Async/await       | ✅      |
| Modules           | ✅      |
| Immutable updates | ✅      |
| Rendering arrays  | ✅      |

---

# 🚀 What To Learn Next

Now you are ready for:

1. React Components
2. JSX
3. Props
4. State
5. Events
6. Hooks
7. React Router
8. API fetching in React

---

# 📘 Recommended Next Tutorials

* [React Documentation](https://react.dev?utm_source=chatgpt.com)
* [MDN JavaScript Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide?utm_source=chatgpt.com)
* [JavaScript.info](https://javascript.info?utm_source=chatgpt.com)

If you want, I can also provide:

1. A **30-Day JavaScript for React Mastery Plan**
2. A **React ES6 Deep Dive**
3. A **JavaScript Exercises Workbook for React**
4. A **DOM-to-React Transition Bootcamp**
5. A **React Project Preparation Series**
6. A **JavaScript Patterns Used in React Tutorial**

