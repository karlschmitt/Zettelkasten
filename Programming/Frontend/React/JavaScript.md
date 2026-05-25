---
id: 20260508190831
title: Master the JavaScript Prerequisites
author: Karl Schmitt
date: 2026-05-08
keywords: [ React, JavaScript ]
---

# Master the JavaScript Prerequisites

To master React, you don't need to know *all* of JavaScript, but you must be comfortable with **ES6+ syntax**. React relies heavily on these specific concepts.

Here is a focused tutorial on the "Big 7" JavaScript prerequisites.

---

### 1. `let` and `const`
In React, we almost never use `var`.
*   `const`: Use this for everything by default (variables that won't be reassigned).
*   `let`: Use this only if you know the value will change.

**React Connection:** Most of your components and data (state) will be defined using `const`.

---

### 2. Arrow Functions
Arrow functions are shorter and are the standard way to write components and event handlers.

```javascript
// Traditional Function
function sayHello() {
  return "Hello!";
}

// Arrow Function
const sayHello = () => "Hello!"; // Implicit return (no 'return' keyword needed if one line)

// With parameters
const add = (a, b) => a + b;
```

**React Connection:** Functional components are written as arrow functions: 
`const App = () => { ... }`

---

### 3. Template Literals
Stop using `+` to join strings. Use backticks (`` ` ``) and `${}`.

```javascript
const name = "Alice";
const greeting = `Hello, ${name}!`; 

// Very useful for dynamic CSS classes
const className = `btn ${isActive ? 'btn-active' : 'btn-disabled'}`;
```

---

### 4. Destructuring (Critical)
This allows you to "unpack" values from arrays or properties from objects into distinct variables.

**Object Destructuring:**
```javascript
const user = { name: "John", age: 25, country: "USA" };

// Instead of user.name and user.age:
const { name, age } = user;
console.log(name); // "John"
```

**Array Destructuring:**
```javascript
const colors = ["red", "green", "blue"];
const [firstColor, secondColor] = colors;
console.log(firstColor); // "red"
```

**React Connection:** This is exactly how we use Hooks: `const [count, setCount] = useState(0);`

---

### 5. The Spread Operator (`...`)
The spread operator allows you to copy the contents of an existing array or object into a new one.

```javascript
const original = { name: "John", role: "Admin" };

// Create a copy and change one value
const updated = { ...original, role: "User" }; 

const nums = [1, 2, 3];
const newNums = [...nums, 4]; // [1, 2, 3, 4]
```

**React Connection:** In React, you **never** mutate state directly. You always create a *copy* of the state with the changes using the spread operator.

---

### 6. Array Methods (`.map()` and `.filter()`)
React uses these instead of `for` loops to handle lists of data.

**`.map()`** (Transforms an array):
```javascript
const users = [{id: 1, name: "A"}, {id: 2, name: "B"}];

// Convert data into a list of strings
const names = users.map((user) => user.name); // ["A", "B"]
```

**`.filter()`** (Removes items):
```javascript
const prices = [10, 50, 100, 200];
const cheapItems = prices.filter(p => p < 100); // [10, 50]
```

**React Connection:** `.map()` is the standard way to render a list of components (like a list of Tweets or products) in the UI.

---

### 7. Async / Await & Fetch
You need to know how to grab data from an external API.

```javascript
const fetchData = async () => {
  try {
    const response = await fetch('https://api.example.com/data');
    const data = await response.json();
    console.log(data);
  } catch (error) {
    console.error("Error fetching data:", error);
  }
};
```

**React Connection:** You will use this inside the `useEffect` hook to load data when a page opens.

---

### 8. ES Modules (Import/Export)
React apps are split into many files. You need to know how to connect them.

**File: `Tools.js`**
```javascript
export const add = (a, b) => a + b;
export default function multiply(a, b) { return a * b; }
```

**File: `App.js`**
```javascript
import multiply, { add } from './Tools.js';
```
---

### How to practice this:
1.  Open your browser console (F12 -> Console).
2.  Try to write a `.map()` function that takes an array of numbers and returns their squares.
3.  Try to destructure a nested object (e.g., `const user = { info: { name: "Bob" } }`).
4.  **Once you can do these without looking at a cheat sheet, you are 100% ready for React.**